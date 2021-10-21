#include "IRRepeater.h"
#include <M5StickC.h>
#include "AppState.h"

#include "states/StateWait.h"

/* -------------------------------- */
void StateWait::onEnter(AppState *app_state, IState *from_state)
{
    setBanner("PRESS A TO RECORD", BLACK, DARKGREY, WHITE);
}

/* -------------------------------- */
void StateWait::loop(AppState *app_state)
{
    M5.update();

    if (M5.BtnA.wasPressed())
    {
        app_state->changeState(STATE_RECORDING);
    }
}