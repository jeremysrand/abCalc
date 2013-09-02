/* 
    abCalcNDA.c
        By: Jeremy Rand
 */


#pragma nda NDAOpen NDAClose NDAAction NDAInit -1 0xFFFF "  abCalc\\H**"


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
#include <Scrap.h>

#include <string.h>
#include <stdlib.h>

#include "abCalcNDA.defs"
#include "abCalc.h"
#include "abCStack.h"
#include "abCError.h"

#include "expr/abCExpr.h"

#include "ops/abCOp.h"


#define MIN_STACK_ITEMS 4

void UpdateStack(void);


typedef struct listElement {
    char *memPtr;
    Byte memFlag;
} listElement;


static BOOLEAN gListStarted = FALSE;
static Handle gSANEDirectPage = NULL;

static BOOLEAN gCalcActive = FALSE;
static GrafPortPtr gCalcWinPtr = NULL;
static unsigned int gUserId;
static unsigned int gResourceId;
listElement *gOpList = NULL;
listElement gStackList[AB_CALC_STACK_DEPTH];
abCalcExpr gNDAExpr;

static Str255 gStrBuf;
static int gSelectedStackItem = -1;

char *gBuffer = NULL;


void NDAClose(void)
{
    int i;

    if (gCalcActive) {
        CloseWindow(gCalcWinPtr);
        gCalcWinPtr = NULL;
        gCalcActive = FALSE;
    }

    if (gBuffer != NULL) {
        free(gBuffer);
        gBuffer = NULL;
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

        if (!ListStatus()) {
            LoadOneTool(0x1c, 0);
            ListStartUp();
            gListStarted = TRUE;
        }

        if (!SANEStatus()) {
            LoadOneTool(0x0a, 0);
            gSANEDirectPage = NewHandle(256, gUserId, 
                    attrBank | attrFixed | attrLocked | attrPage, NULL);
            SANEStartUp((Word) *gSANEDirectPage);
        }

        abCalcInit();

        for (i = 0; i < AB_CALC_STACK_DEPTH; i++) {
            gStackList[i].memPtr = NULL;
        }
    } else {
        if (gSANEDirectPage) {
            SANEShutDown();
            DisposeHandle(gSANEDirectPage);
            UnloadOneTool(0x0a);
            gSANEDirectPage = NULL;
        }

        if (gListStarted) {
            ListShutDown();
            UnloadOneTool(0x1c);
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
    int numToDisplay = abCalcStackNumItems();

    if (numToDisplay < MIN_STACK_ITEMS) {
        numToDisplay = MIN_STACK_ITEMS;
    }

    stackListCtl = (Handle)GetCtlHandleFromID(gCalcWinPtr, abCalcStackList);

    for (i = numToDisplay - 1; i >= 0; i--) {
        if (gStackList[i].memPtr == NULL) {
            gStackList[i].memPtr = malloc(AB_CALC_EXPR_STRING_MAX + 8);
        }
        abCalcStackExprStringAt(numToDisplay - i - 1, gStackList[i].memPtr,
                TRUE);
        gStackList[i].memFlag = 0;
    }

    NewList2(NULL, numToDisplay - 3, (Ref)gStackList, 0, numToDisplay, stackListCtl);
    gSelectedStackItem = -1;
}


BOOLEAN ErrorRaised(void)
{
    char *errorString = abCalcGetError();
    if (errorString == NULL) {
        return FALSE;
    }

    AlertWindow(awCString+awResource, (Pointer)&errorString, abCalcErrorAlert);

    abCalcClearError(); 
    return TRUE;
}


void PushCalcEntry(CtlRecHndl entryBox)
{
    abCalcOp *op;

    GetLETextByID(gCalcWinPtr, abCalcEntryBox, &gStrBuf);
    
    if (gStrBuf.textLength > 0) {
        gStrBuf.text[gStrBuf.textLength] = '\0';

        op = abCalcOpLookup(gStrBuf.text);

        if (op != NULL) {
            op->execute();
        } else if (abCalcParseExpr(&gNDAExpr, gStrBuf.text) != NULL) {
            abCalcStackExprPush(&gNDAExpr);
        } else {
            LERecHndl leHandle;

            HLock((Handle)entryBox);
            leHandle = (LERecHndl)(*entryBox)->ctlData;
            HUnlock((Handle)entryBox);

            LESetSelect(0, gStrBuf.textLength, leHandle);
            abCalcRaiseError(abCalcSyntaxError, NULL);
            return;
        }
    
        gStrBuf.textLength = 0;
        SetLETextByID(gCalcWinPtr, abCalcEntryBox, &gStrBuf);
    }
}


void ExecCalcCmd(char *cmd)
{
    abCalcOp *op = abCalcOpLookup(cmd);
    CtlRecHndl entryBox = GetCtlHandleFromID(gCalcWinPtr, abCalcEntryBox);

    PushCalcEntry(entryBox);

    if ((!ErrorRaised()) &&
        (op != NULL)) {
        op->execute();
    }

    ErrorRaised();
    
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


void ExecMinusButton(void)
{
    int i;
    char aChar;
    BOOLEAN doCmd = FALSE;
    BOOLEAN dotSeen = FALSE;

    CtlRecHndl entryBox = GetCtlHandleFromID(gCalcWinPtr, abCalcEntryBox);
    GetLETextByID(gCalcWinPtr, abCalcEntryBox, &gStrBuf);

    if (gStrBuf.textLength > 0) {
        doCmd = TRUE;

        gStrBuf.text[gStrBuf.textLength] = '\0';

        aChar = gStrBuf.text[gStrBuf.textLength - 1];
        if (((aChar == 'e') ||
             (aChar == 'E')) &&
            (gStrBuf.textLength > 1)) {
            doCmd = FALSE;
            for (i = 0; i < gStrBuf.textLength - 1; i++) {
                switch (gStrBuf.text[i]) {
                    case '-':
                        if (i != 0) {
                            doCmd = TRUE;
                        }
                        break;

                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        break;

                    case '.':
                        if (dotSeen) {
                            doCmd = TRUE;
                        } else {
                            dotSeen = TRUE;
                        }
                        break;

                    default:
                        doCmd = TRUE;
                        break;
                }
                if (doCmd)
                    break;
            }
        }
    }

    if (doCmd) {
        ExecCalcCmd("-");
    } else {
        InsertChar(entryBox, '-');
    }

    return;
}


void HandleEntryBox(void)
{
    Handle stackListCtl = (Handle)GetCtlHandleFromID(gCalcWinPtr, abCalcStackList);
    if (gSelectedStackItem != -1) {
        ResetMember2(stackListCtl);
        DrawMember2(gSelectedStackItem, stackListCtl);
        gSelectedStackItem = -1;
    }
}


void HandleStackClick(void)
{
    Handle stackListCtl = (Handle)GetCtlHandleFromID(gCalcWinPtr, abCalcStackList);
    int nthOp;
    int numStackItems = abCalcStackNumItems();
    int numDisplayed = numStackItems;
    int selectedStackItem = -1;

    nthOp = NextMember2(0, stackListCtl);
    if (nthOp == gSelectedStackItem) {
        ResetMember2(stackListCtl);
        DrawMember2(gSelectedStackItem, stackListCtl);
        gSelectedStackItem = -1;
        nthOp = NextMember2(0, stackListCtl);
    }
    if (nthOp == 0)
        return;

    if (numDisplayed < MIN_STACK_ITEMS)
        numDisplayed = MIN_STACK_ITEMS;

    selectedStackItem = numDisplayed + 1 - nthOp;

    if (selectedStackItem > numStackItems) {
        ResetMember2(stackListCtl);
        DrawMember2(nthOp, stackListCtl);
        gSelectedStackItem = -1;
    } else {
        gSelectedStackItem = nthOp;
    }
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

            if (!ErrorRaised()) {
                op->execute();
            }

            ErrorRaised();

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
            ErrorRaised();
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
            ExecMinusButton();
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
            HandleEntryBox();
            break;

        case abCalcStackList:
            HandleStackClick();
            break;

        case abCalcOpList:
            HandleOpClick();
            break;
    }
}


void DoCut(void)
{
    LERecHndl leHandle;
    CtlRecHndl entryBox = GetCtlHandleFromID(gCalcWinPtr, abCalcEntryBox);

    HLock((Handle)entryBox);
    leHandle = (LERecHndl)(*entryBox)->ctlData;
    HUnlock((Handle)entryBox);

    LECut(leHandle);
    LEToScrap();
}


void DoCopy(void)
{
    Handle stackListCtl = (Handle)GetCtlHandleFromID(gCalcWinPtr, abCalcStackList);
    LERecHndl leHandle;
    CtlRecHndl entryBox = GetCtlHandleFromID(gCalcWinPtr, abCalcEntryBox);

    int numStackItems = abCalcStackNumItems();
    int numDisplayed = numStackItems;
    int selectedStackItem;

    if (gSelectedStackItem == -1) {
        HLock((Handle)entryBox);
        leHandle = (LERecHndl)(*entryBox)->ctlData;
        HUnlock((Handle)entryBox);

        LECopy(leHandle);
        LEToScrap();
        return;
    }

    if (numDisplayed < MIN_STACK_ITEMS)
        numDisplayed = MIN_STACK_ITEMS;

    selectedStackItem = numDisplayed - gSelectedStackItem;

    if (gBuffer == NULL) {
        gBuffer = malloc(AB_CALC_EXPR_STRING_MAX);
    }

    if ((selectedStackItem >= 0) &&
        (selectedStackItem < numStackItems) &&
        (abCalcStackExprStringAt(selectedStackItem, gBuffer, FALSE) != NULL)) {
        ZeroScrap();
        PutScrap(strlen(gBuffer), textScrap, gBuffer);
    }

    SetPort(gCalcWinPtr);
    ResetMember2(stackListCtl);
    DrawMember2(gSelectedStackItem, stackListCtl);
    gSelectedStackItem = -1;
}


void DoPaste(void)
{
    LERecHndl leHandle;
    CtlRecHndl entryBox = GetCtlHandleFromID(gCalcWinPtr, abCalcEntryBox);

    HLock((Handle)entryBox);
    leHandle = (LERecHndl)(*entryBox)->ctlData;
    HUnlock((Handle)entryBox);

    LEFromScrap();
    LEPaste(leHandle);
}


void DoClear(void)
{
    LERecHndl leHandle;
    CtlRecHndl entryBox = GetCtlHandleFromID(gCalcWinPtr, abCalcEntryBox);

    HLock((Handle)entryBox);
    leHandle = (LERecHndl)(*entryBox)->ctlData;
    HUnlock((Handle)entryBox);

    LEDelete(leHandle);
}


void HandleMenu(int menuItem)
{
    SetPort(gCalcWinPtr);

    switch (menuItem) {
        case cutAction:
            DoCut();
            break;

        case copyAction:
            DoCopy();
            break;

        case pasteAction:
            DoPaste();
            break;

        case clearAction:
            DoClear();
            break;

        default:
            break;
    }
}


void HandleKey(EventRecord *event)
{
    BOOLEAN appleKeyPressed = ((event->modifiers & appleKey) != 0);
    char key = (event->message & 0xff);

    if (!appleKeyPressed)
        return;

    switch (key) {
        case 'C':
        case 'c':
            DoCopy();
            break;

        case 'X':
        case 'x':
            DoCut();
            break;

        case 'V':
        case 'v':
            DoPaste();
            break;
    }
}


BOOLEAN NDAAction(EventRecord *sysEvent, int code)
{
    int event;
    static EventRecord localEvent;
    unsigned int eventCode;
    BOOLEAN result = FALSE;

    switch (code) {
        case runAction:
            return result;

        case eventAction:
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

                case keyDownEvt:
                case autoKeyEvt:
                    HandleKey(&localEvent);
                    break;
            }
            break;

        case cutAction:
        case copyAction:
        case pasteAction:
        case clearAction:
            result = TRUE;
            HandleMenu(code);
            break;
    }

    return result;
}
