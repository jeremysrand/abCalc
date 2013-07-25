/* 
    abCalcNDA.c
        By: Jeremy Rand
 */


#pragma nda NDAOpen NDAClose NDAAction NDAInit 60 0x03FF "  abCalc\\H**"


#include <types.h>


static BOOLEAN gCalcActive;
static GrafPortPtr gCalcWinPtr;


void NDAClose(void)
{
    if (gCalcActive) {
        CloseWindow(gCalcWinPtr);
        gCalcActive = FALSE;
    }
}


void NDAInit(int code)
{
    if (code == 1)
        gCalcActive = FALSE;
    else if (gCalcActive)
        NDAClose();
}


GrafPortPtr NDAOpen(void)
{
    GrafPortPtr wPtr;

    wPtr = NULL;
    if (!clockActive) {
        if (OpenResourceFork()) {
            gCalcWinPtr = NewWindow2("\p abCalc ", 0, NULL, NULL, 0x02, wrNum, rWindParam1);
            if (toolerror() == 0) {
                SetSysWindow(gCalcWinPtr);
                clockActive = TRUE;
                wPtr = clockWinPtr;
            }
            CloseResourceFork();
        }
    }
    return wPtr;
}


BOOLEAN NDAAction(int code, EventRecord *sysEvent)
{
    int event;
    static EventRecord localEvent;

    switch (code) {
        case eventAction:
            localEvent.what = sysEvent->what;
            localEvent.message = sysEvent->message;
            localEvent.when = sysEvent->when;
            localEvent.where = sysEvent->where;
            localEvent.modifiers = sysEvent->modifiers;
            event = TaskMasterDA(0, &localEvent);
            break;
        case runAction:
            break;
    }
    return FALSE;
}
