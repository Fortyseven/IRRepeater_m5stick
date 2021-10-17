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


// IRData last_scan;

// bool has_packet = false;
// bool printed_wait_msg = false;

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
}

/* --------------------------------------------------------------------- */
// void stateWait()
// {
//     M5.update();

//     if (!printed_wait_msg)
//     {
//         tb_display_print_String("Press M5 button to record.\n");

//         if (has_packet)
//         {
//             tb_display_print_String("Press secondary button to playback.\n");
//         }
//         printed_wait_msg = true;
//     }

//     if (M5.BtnA.wasPressed())
//     {
//         switchState(RECORDING);
//         IrReceiver.begin(RECV_PIN);
//         tb_display_clear();
//         tb_display_print_String("\nWaiting for packet...");
//     }
//     else if (M5.BtnB.wasPressed())
//     {
//         // tb_display_print_String("\nB");
//         tb_display_print_String((char *)getProtocolString(last_scan.protocol));
//     }
// }

/* --------------------------------------------------------------------- */
// void stateRecording()
// {
//     if (IrReceiver.decode())
//     {
//         if (IrReceiver.decodedIRData.decodedRawData != 0)
//         {
//             tb_display_clear();

//             tb_display_print_String("\nPRO: ");
//             tb_display_print_String((char *)getProtocolString(IrReceiver.decodedIRData.protocol));

//             tb_display_print_String("\nCMD: ");
//             tb_display_print_String(toString(IrReceiver.decodedIRData.command));

//             tb_display_print_String("\nADR: ");
//             tb_display_print_String(toString(IrReceiver.decodedIRData.address));

//             tb_display_print_String("\nFLG: ");
//             tb_display_print_String(toString(IrReceiver.decodedIRData.flags));

//             tb_display_print_String("\nRAW: ");
//             tb_display_print_String(toString(IrReceiver.decodedIRData.decodedRawData));

//             memcpy(&last_scan, &IrReceiver.decodedIRData, sizeof(IRData));

//             has_packet = true;
//             switchState(WAIT);
//         }
//         IrReceiver.resume();
//     }
// }



/* --------------------------------------------------------------------- */
void loop()
{
    app_state->loop();
}
