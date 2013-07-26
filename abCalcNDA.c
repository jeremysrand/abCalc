/* 
    abCalcNDA.c
        By: Jeremy Rand
 */


#pragma nda NDAOpen NDAClose NDAAction NDAInit 0 0xFFFF "  abCalc\\H**"


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

#include "abCalcNDA.defs"
#include "abCalc.h"


static BOOLEAN gCalcActive = FALSE;
static GrafPortPtr gCalcWinPtr = NULL;
static unsigned int gUserId;
static unsigned int gResourceId;


void NDAClose(void)
{
    if (gCalcActive) {
        CloseWindow(gCalcWinPtr);
        gCalcWinPtr = NULL;
        gCalcActive = FALSE;
    }
    CloseResourceFile(gResourceId);
    ResourceShutDown();
}


void NDAInit(int code)
{
    if (code) {
        gCalcActive = FALSE;
        gUserId = MMStartUp();
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

    gCalcActive = TRUE;

    prefsDCB.preferences = oldPrefs;
    SetSysPrefsGS(&prefsDCB);

    levelDCB.level = oldLevel;
    SetLevelGS(&levelDCB);

    SetCurResourceApp(oldResourceApp);

    return gCalcWinPtr;
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
