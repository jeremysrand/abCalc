/* 
    abCalcNDA.c
        By: Jeremy Rand
 */


#pragma nda NDAOpen NDAClose NDAAction NDAInit 0 0xFFFF "  abCalc\\H**"
#pragma stacksize 4096


#include <orca.h>
#include <GSOS.h>
#include <QuickDraw.h>
#include <Window.h>
#include <Desk.h>
#include <Resources.h>
#include <Memory.h>
#include <Loader.h>
#include <Control.h>
#include <Event.h>
#include <List.h>

#include <string.h>
#include <stdlib.h>

#include "abCalcNDA.defs"
#include "abCalc.h"
#include "abCStack.h"
#include "abCError.h"

#include "expr/abCExpr.h"

#include "ops/abCOp.h"


void UpdateStack(Boolean draw);


typedef struct listElement {
    char *memPtr;
    Byte memFlag;
} listElement;


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
    int numOps;

    if (gCalcActive) {
        CloseWindow(gCalcWinPtr);
        gCalcWinPtr = NULL;
        gCalcActive = FALSE;

        numOps = abCalcOpNumOps();
        for (i = 0; i < numOps; i++) {
            free(gOpList[i].memPtr);
        }
        free(gOpList);
        gOpList = NULL;

        for (i = 0; i < AB_CALC_STACK_DEPTH; i++) {
            if (gStackList[i].memPtr != NULL) {
                free(gStackList[i].memPtr);
                gStackList[i].memPtr = NULL;
            }
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
        abCalcInit();

        for (i = 0; i < AB_CALC_STACK_DEPTH; i++) {
            gStackList[i].memPtr = NULL;
        }
    } else if (gCalcActive) {
        NDAClose();
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

    UpdateStack(FALSE);

    gCalcActive = TRUE;

    prefsDCB.preferences = oldPrefs;
    SetSysPrefsGS(&prefsDCB);

    levelDCB.level = oldLevel;
    SetLevelGS(&levelDCB);

    SetCurResourceApp(oldResourceApp);

    return gCalcWinPtr;
}


void UpdateStack(BOOLEAN draw)
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
        abCalcStackExprStringAt(i, gStackList[i].memPtr);
        gStackList[i].memFlag = 0;
    }

    NewList2(NULL, 1, (Ref)gStackList, 0, numToDisplay, stackListCtl);

    if (draw)
        DrawMember2(0, stackListCtl);
}


void DoCalcStuff(char *cmd)
{
    abCalcOp *op = abCalcOpLookup(cmd);

    if (op != NULL) {
        op->execute();
    } else if (abCalcParseExpr(&gNDAExpr, cmd) != NULL) {
        abCalcStackExprPush(&gNDAExpr);
    } else {
        abCalcRaiseError(abCalcSyntaxError, NULL);
    }
    
    UpdateStack(TRUE);
}


void HandleControl(EventRecord *event)
{
    static Str255 strBuf;
    CtlRecHndl entryBox = GetCtlHandleFromID(gCalcWinPtr, abCalcEntryBox);

    switch (event->wmTaskData4) {
        case abCalcBtn0:
            break;

        case abCalcBtn1:
            break;

        case abCalcBtn2:
            break;

        case abCalcBtn3:
            break;

        case abCalcBtn4:
            break;

        case abCalcBtn5:
            break;

        case abCalcBtn6:
            break;

        case abCalcBtn7:
            break;

        case abCalcBtn8:
            break;

        case abCalcBtn9:
            break;

        case abCalcBtnEnter:
            GetLETextByID(gCalcWinPtr, abCalcEntryBox, &strBuf);
            strBuf.text[strBuf.textLength] = '\0';
            DoCalcStuff(strBuf.text);
            strBuf.textLength = 0;
            SetLETextByID(gCalcWinPtr, abCalcEntryBox, &strBuf);
            break;

        case abCalcBtnDot:
            break;

        case abCalcBtnNum:
            break;

        case abCalcBtnAdd:
            DoCalcStuff("+");
            break;

        case abCalcBtnSub:
            DoCalcStuff("-");
            break;

        case abCalcBtnMult:
            DoCalcStuff("*");
            break;

        case abCalcBtnDiv:
            DoCalcStuff("/");
            break;

        case abCalcBtnPow:
            DoCalcStuff("^");
            break;

        case abCalcBtnA:
            break;

        case abCalcBtnB:
            break;

        case abCalcBtnC:
            break;

        case abCalcBtnD:
            break;

        case abCalcBtnE:
            break;

        case abCalcBtnF:
            break;

        case abCalcEntryBox:
            break;

        case abCalcStackList:
            break;

        case abCalcOpList:
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


/* I shouldn't need a main() but the linker seems to want one when I
   link multiple objects together in the final link step.  If I only
   have a single object, there is no problem.  There is probable a
   compile incantation which will avoid this but for now... */
int main(void)
{
    return 0;
}
