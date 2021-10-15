#include "IRRepeater.h"
#include <M5StickC.h>
#include "tb_display.h"
#include "AppState.h"

#include "states/StateWait.h"

/* -------------------------------- */
void StateWait::onEnter(AppState *app_state, IState *from_state)
{
    tb_display_print_String("Hello from WAIT state.\n");
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