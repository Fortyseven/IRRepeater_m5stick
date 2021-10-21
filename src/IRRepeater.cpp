// include this instead of IRremote.h to avoid compilation errors
// https://github.com/Arduino-IRremote/Arduino-IRremote/issues/805
// #include <IRremoteInt.h>
#include <IRRepeater.h>
#include <M5StickC.h>
#include "tb_display.h"

#include "AppState.h"

#include "states/StateWait.h"
#include "states/StateRecording.h"
#include "states/StatePlayback.h"


bool has_scan = false;

IRData last_scan;       // used for known protocols
uint8_t last_raw[100];  // used for UNKNOWN protocols

AppState *app_state;

/* --------------------------------------------------------------------- */
void setup()
{
    M5.begin();

    tb_display_init(3);

    app_state = new AppState();

    app_state->registerState(new StateWait(), STATE_WAIT);
    app_state->registerState(new StateRecording(), STATE_RECORDING);
    app_state->registerState(new StatePlayback(), STATE_PLAYBACK);

    app_state->changeState(STATE_WAIT);
    // app_state->changeState(STATE_PLAYBACK);
}

/* --------------------------------------------------------------------- */
void loop()
{
    app_state->loop();
}
