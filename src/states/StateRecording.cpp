#include "IRRepeater.h"
#include "IRremote.h"
#include <M5StickC.h>
#include "tb_display.h"
#include "AppState.h"

#include "states/StateRecording.h"

void StateRecording::onEnter(AppState *app_state, IState *from_state)
{
    tb_display_print_String("Hello from REC state.\n");
    IrReceiver.begin(IR_RECV_PIN);
}

/* -------------------------------- */
void StateRecording::loop(AppState *app_state)
{
    if (IrReceiver.decode())
    {
        if (IrReceiver.decodedIRData.decodedRawData != 0)
        {
            tb_display_clear();

            tb_display_print_String("\nPRO: ");
            tb_display_print_String((char *)getProtocolString(IrReceiver.decodedIRData.protocol));

            tb_display_print_String("\nCMD: ");
            tb_display_print_String(toString(IrReceiver.decodedIRData.command));

            tb_display_print_String("\nADR: ");
            tb_display_print_String(toString(IrReceiver.decodedIRData.address));

            tb_display_print_String("\nFLG: ");
            tb_display_print_String(toString(IrReceiver.decodedIRData.flags));

            tb_display_print_String("\nRAW: ");
            tb_display_print_String(toString(IrReceiver.decodedIRData.decodedRawData));

            // memcpy(&last_scan, &IrReceiver.decodedIRData, sizeof(IRData));

            // has_packet = true;
            app_state->changeState(STATE_WAIT);
        }
        IrReceiver.resume();
        app_state->changeState(STATE_WAIT);
    }
}