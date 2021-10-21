#include "IRRepeater.h"
#include "IRremoteInt.h"
#include <M5StickC.h>
#include "AppState.h"

#include "states/StatePlayback.h"

/* -------------------------------- */
void StatePlayback::onEnter(AppState *app_state, IState *from_state)
{
    char msg[100];

    if (last_scan.protocol == UNKNOWN)
    {
        sprintf(msg, "PLAYBACK RAW: %x", last_scan.decodedRawData);
        setBanner(msg, DARKCYAN, CYAN, RED);
    }
    else
    {
        sprintf(msg, "PLAYBACK %s / %x", (char *)getProtocolString(last_scan.protocol), last_scan.command);
        setBanner(msg, DARKCYAN, CYAN, BLACK);
    }

    M5.Lcd.setTextColor(CYAN);
    IrSender.begin(9, false);
}

/* -------------------------------- */
void StatePlayback::loop(AppState *app_state)
{
    M5.update();
    if (M5.BtnA.wasPressed())
    {
        app_state->changeState(STATE_WAIT);
    }
    else if (has_scan)
    {
        M5.Lcd.print('.');
        IrSender.sendRaw(last_raw, 100, 38);
        delay(500);
    }
}