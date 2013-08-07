/* 
    abCalcNDA.c
        By: Jeremy Rand
 */


#pragma nda NDAOpen NDAClose NDAAction NDAInit 0 0xFFFF "  abCalc\\H**"
#pragma stacksize 2048


#include <orca.h>
#include <GSOS.h>
#include <Locator.h>
#include <QuickDraw.h>
#include <Window.h>
#include <Desk.h>
#include <Resources.h>
#include <Memory.h>
#include <Loader.h>
#include <Control.h>
#include <Event.h>
#include <List.h>
#include <Sane.h>
#include <LineEdit.h>

#include <string.h>
#include <stdlib.h>

#include "abCalcNDA.defs"
#include "abCalc.h"
#include "abCStack.h"
#include "abCError.h"

#include "expr/abCExpr.h"

#include "ops/abCOp.h"


void UpdateStack(void);


typedef struct listElement {
    char *memPtr;
    Byte memFlag;
} listElement;


static ToolTable gToolTable = {
    2,
    { { 0x1c, 0 },      /* List Manager */
      { 0x0a, 0 } }     /* SANE */
};

static BOOLEAN gListStarted = FALSE;
static BOOLEAN gSANEStarted = FALSE;

static BOOLEAN gCalcActive = FALSE;
static GrafPortPtr gCalcWinPtr = NULL;
static unsigned int gUserId;
static unsigned int gResourceId;
listElement *gOpList = NULL;
listElement gStackList[AB_CALC_STACK_DEPTH];
abCalcExpr gNDAExpr;



void NDAClose(void)
{
    int i;

    if (gCalcActive) {
        CloseWindow(gCalcWinPtr);
        gCalcWinPtr = NULL;
        gCalcActive = FALSE;
    }

    if (gOpList != NULL) {
        free(gOpList);
        gOpList = NULL;
    }

    for (i = 0; i < AB_CALC_STACK_DEPTH; i++) {
        if (gStackList[i].memPtr != NULL) {
            free(gStackList[i].memPtr);
            gStackList[i].memPtr = NULL;
        }
    }

    CloseResourceFile(gResourceId);
    ResourceShutDown();
}


void NDAInit(int code)
{
    int i;

    if (code) {
        gCalcActive = FALSE;
        gUserId = MMStartUp();

        LoadTools((Pointer)&gToolTable);

        if (!ListStatus()) {
            ListStartUp();
            gListStarted = TRUE;
        }

        if (!SANEStatus()) {
            Handle hdl = NewHandle(256, gUserId, 
                    attrBank | attrFixed | attrLocked | attrPage, NULL);
            SANEStartUp((Word) *hdl);
            gSANEStarted = TRUE;
        }

        abCalcInit();

        for (i = 0; i < AB_CALC_STACK_DEPTH; i++) {
            gStackList[i].memPtr = NULL;
        }
    } else if (gCalcActive) {
        NDAClose();

        if (gSANEStarted) {
            SANEShutDown();
            gSANEStarted = FALSE;
        }

        if (gListStarted) {
            ListShutDown();
            gListStarted = FALSE;
        }
    }
}


#pragma databank 1
void DrawContents(void)
{
    PenNormal();
    DrawControls(GetPort());
}
#pragma databank 0


GrafPortPtr NDAOpen(void)
{
    Pointer pathToSelf;
    unsigned int oldResourceApp;
    LevelRecGS levelDCB;
    unsigned int oldLevel;
    SysPrefsRecGS prefsDCB;
    unsigned int oldPrefs;
    int numOps;
    int i;
    Handle opListCtl;

    if (gCalcActive)
        return NULL;

    oldResourceApp = GetCurResourceApp();
    ResourceStartUp(gUserId);
    pathToSelf = LGetPathname2(gUserId, 1);

    levelDCB.pCount = 2;
    GetLevelGS(&levelDCB);
    oldLevel = levelDCB.level;
    levelDCB.level = 0;
    SetLevelGS(&levelDCB);

    prefsDCB.pCount = 1;
    GetSysPrefsGS(&prefsDCB);
    oldPrefs = prefsDCB.preferences;
    prefsDCB.preferences = (prefsDCB.preferences & 0x1fff) | 0x8000;
    SetSysPrefsGS(&prefsDCB);

    gResourceId = OpenResourceFile(readEnable, NULL, pathToSelf);

    gCalcWinPtr = NewWindow2("\p abCalc ", 0, DrawContents, NULL, refIsResource,
        abCalcWinNum, rWindParam1);

    SetSysWindow(gCalcWinPtr);
    ShowWindow(gCalcWinPtr);
    SelectWindow(gCalcWinPtr);
    SetPort(gCalcWinPtr);

    if (gOpList == NULL) {
        numOps = abCalcOpNumOps();
        gOpList = malloc(sizeof(*gOpList) * numOps);
        for (i = 0; i < numOps; i++) {
            gOpList[i].memPtr = abCalcOpNth(i)->name;
            gOpList[i].memFlag = 0;
        }
    }

    opListCtl = (Handle)GetCtlHandleFromID(gCalcWinPtr, abCalcOpList);
    NewList2(NULL, 1, (Ref)gOpList, 0, numOps, opListCtl);

    UpdateStack();

    gCalcActive = TRUE;

    prefsDCB.preferences = oldPrefs;
    SetSysPrefsGS(&prefsDCB);

    levelDCB.level = oldLevel;
    SetLevelGS(&levelDCB);

    SetCurResourceApp(oldResourceApp);

    return gCalcWinPtr;
}


void UpdateStack(void)
{
    Handle stackListCtl;
    int i;
    int numOnStack = abCalcStackNumItems();
    int numToDisplay = numOnStack;

    if (numToDisplay < 4) {
        numToDisplay = 4;
    }

    stackListCtl = (Handle)GetCtlHandleFromID(gCalcWinPtr, abCalcStackList);

    for (i = numToDisplay - 1; i >= 0; i--) {
        if (gStackList[i].memPtr == NULL) {
            gStackList[i].memPtr = malloc(AB_CALC_EXPR_STRING_MAX + 8);
        }
        abCalcStackExprStringAt(numToDisplay - i - 1, gStackList[i].memPtr);
        gStackList[i].memFlag = 0;
    }

    NewList2(NULL, 1, (Ref)gStackList, 0, numToDisplay, stackListCtl);

    SelectMember2(numToDisplay, stackListCtl);
    ResetMember2(stackListCtl);
}


void PushCalcEntry(CtlRecHndl entryBox)
{
    static Str255 strBuf;
    abCalcOp *op;

    GetLETextByID(gCalcWinPtr, abCalcEntryBox, &strBuf);
    
    if (strBuf.textLength > 0) {
        strBuf.text[strBuf.textLength] = '\0';

        op = abCalcOpLookup(strBuf.text);

        if (op != NULL) {
            op->execute();
        } else if (abCalcParseExpr(&gNDAExpr, strBuf.text) != NULL) {
            abCalcStackExprPush(&gNDAExpr);
        } else {
            abCalcRaiseError(abCalcSyntaxError, NULL);
            return;
        }
    
        strBuf.textLength = 0;
        SetLETextByID(gCalcWinPtr, abCalcEntryBox, &strBuf);
    }
}


void ExecCalcCmd(char *cmd)
{
    abCalcOp *op = abCalcOpLookup(cmd);
    CtlRecHndl entryBox = GetCtlHandleFromID(gCalcWinPtr, abCalcEntryBox);

    PushCalcEntry(entryBox);

    if (op != NULL) {
        op->execute();
    }
    
    UpdateStack();
}


void InsertChar(CtlRecHndl entryBox, char ch)
{
    LERecHndl leHandle;

    HLock((Handle)entryBox);
    leHandle = (LERecHndl)(*entryBox)->ctlData;
    HUnlock((Handle)entryBox);

    LEDelete(leHandle);
    LEInsert(&ch, 1, leHandle);
}


void HandleStackClick(void)
{
    Handle stackListCtl = (Handle)GetCtlHandleFromID(gCalcWinPtr, abCalcStackList);

    DrawMember2(ResetMember2(stackListCtl), stackListCtl);
}


void HandleOpClick(void)
{
    Handle opListCtl = (Handle)GetCtlHandleFromID(gCalcWinPtr, abCalcOpList);
    int nthOp = ResetMember2(opListCtl);
    abCalcOp *op;

    if (nthOp > 0) {
        nthOp--;
        
        op = abCalcOpNth(nthOp);
        if (op != NULL) {
            CtlRecHndl entryBox = GetCtlHandleFromID(gCalcWinPtr, abCalcEntryBox);
            PushCalcEntry(entryBox);
            op->execute();
            UpdateStack();
        }

        DrawMember2(nthOp + 1, opListCtl);
    }
}


void HandleControl(EventRecord *event)
{
    CtlRecHndl entryBox = GetCtlHandleFromID(gCalcWinPtr, abCalcEntryBox);
    SetPort(gCalcWinPtr);

    switch (event->wmTaskData4) {
        case abCalcBtn0:
            InsertChar(entryBox, '0');
            break;

        case abCalcBtn1:
            InsertChar(entryBox, '1');
            break;

        case abCalcBtn2:
            InsertChar(entryBox, '2');
            break;

        case abCalcBtn3:
            InsertChar(entryBox, '3');
            break;

        case abCalcBtn4:
            InsertChar(entryBox, '4');
            break;

        case abCalcBtn5:
            InsertChar(entryBox, '5');
            break;

        case abCalcBtn6:
            InsertChar(entryBox, '6');
            break;

        case abCalcBtn7:
            InsertChar(entryBox, '7');
            break;

        case abCalcBtn8:
            InsertChar(entryBox, '8');
            break;

        case abCalcBtn9:
            InsertChar(entryBox, '9');
            break;

        case abCalcBtnEnter:
            PushCalcEntry(entryBox);
            UpdateStack();
            break;

        case abCalcBtnDot:
            InsertChar(entryBox, '.');
            break;

        case abCalcBtnNum:
            InsertChar(entryBox, '#');
            break;

        case abCalcBtnAdd:
            ExecCalcCmd("+");
            break;

        case abCalcBtnSub:
            ExecCalcCmd("-");
            break;

        case abCalcBtnMult:
            ExecCalcCmd("*");
            break;

        case abCalcBtnDiv:
            ExecCalcCmd("/");
            break;

        case abCalcBtnPow:
            ExecCalcCmd("^");
            break;

        case abCalcBtnA:
            InsertChar(entryBox, 'A');
            break;

        case abCalcBtnB:
            InsertChar(entryBox, 'B');
            break;

        case abCalcBtnC:
            InsertChar(entryBox, 'C');
            break;

        case abCalcBtnD:
            InsertChar(entryBox, 'D');
            break;

        case abCalcBtnE:
            InsertChar(entryBox, 'E');
            break;

        case abCalcBtnF:
            InsertChar(entryBox, 'F');
            break;

        case abCalcEntryBox:
            break;

        case abCalcStackList:
            HandleStackClick();
            break;

        case abCalcOpList:
            HandleOpClick();
            break;
    }
}


BOOLEAN NDAAction(EventRecord *sysEvent, int code)
{
    int event;
    static EventRecord localEvent;
    unsigned int eventCode;

    if (code == runAction)
        return FALSE;

    if (code == eventAction) {
        BlockMove((Pointer)sysEvent, (Pointer)&localEvent, 16);
        localEvent.wmTaskMask = 0x001FFFFF;
        eventCode = TaskMasterDA(0, &localEvent);
        switch(eventCode) {
            case updateEvt:
                BeginUpdate(gCalcWinPtr);
                DrawContents();
                EndUpdate(gCalcWinPtr);
                break;

            case wInControl:
                HandleControl(&localEvent);
                break;
        }
    }

    return FALSE;
}
