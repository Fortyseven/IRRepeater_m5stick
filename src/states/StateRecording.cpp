#include "IRRepeater.h"
#include "IRremote.h"
#include <M5StickC.h>
#include "AppState.h"

#include "states/StateRecording.h"

/* -------------------------------- */
void StateRecording::onEnter(AppState *app_state, IState *from_state)
{
    setBanner("RECORDING", MAROON, RED, YELLOW);
    IrReceiver.begin(IR_RECV_PIN);
    Serial.begin(9600);
    has_scan = false;
}

/* -------------------------------- */
void StateRecording::loop(AppState *app_state)
{
    M5.update();
    if (M5.BtnA.wasPressed())
    {
        if (has_scan)
        {
            app_state->changeState(STATE_PLAYBACK);
        }
        else
        {
            app_state->changeState(STATE_WAIT);
        }
    }
    else if (IrReceiver.decode())
    {
        if (IrReceiver.decodedIRData.decodedRawData)
        {
            char msg[100];
            sprintf(msg, "RECEIVED: %s", (char *)getProtocolString(IrReceiver.decodedIRData.protocol));
            setBanner(msg, MAROON, RED, YELLOW);
            M5.Lcd.setTextColor(WHITE);

            if (IrReceiver.decodedIRData.protocol != UNKNOWN)
            {
                M5.Lcd.printf("CMD: %x\n", IrReceiver.decodedIRData.command);

                if (IrReceiver.decodedIRData.address)
                {
                    M5.Lcd.printf("ADR: %x\n", IrReceiver.decodedIRData.address);
                }

                if (IrReceiver.decodedIRData.flags)
                {
                    M5.Lcd.printf("FLG: %x\n", IrReceiver.decodedIRData.flags);
                }
            }

            M5.Lcd.printf("RAW: %x\n", IrReceiver.decodedIRData.decodedRawData);

            memcpy(&last_scan, &IrReceiver.decodedIRData, sizeof(IRData));
            IrReceiver.printIRResultRawFormatted(&Serial);
            IrReceiver.compensateAndStoreIRResultInArray(last_raw);

            has_scan = true;
        }
        IrReceiver.resume();
    }
}