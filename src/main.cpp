#include <IRremote.h>
#include <M5StickC.h>
#include "tb_display.h"

int RECV_PIN = 26;

char str[255] = ""; // FIXME: hello, overflow

char *toString(int val)
{
    snprintf(str, 255, "0x%x", val);
    return str;
}
/* --------------------------------------------------------------------- */
enum APP_STATE
{
    WAIT = 0,
    RECORDING,
    PLAYBACK,
    SCAN
};

int app_state = WAIT;

IRData last_scan;

bool has_packet = false;
bool printed_wait_msg = false;

/* --------------------------------------------------------------------- */
void setup()
{
    M5.begin();

    tb_display_init(3);
    //  Serial.begin(115200);
}

/* --------------------------------------------------------------------- */
void switchState(int state)
{
    //  if (state == WAIT) {
    //    printed_wait_msg = false;
    //  }
    app_state = state;
}

/* --------------------------------------------------------------------- */
void stateWait()
{
    M5.update();

    if (!printed_wait_msg)
    {
        tb_display_print_String("Press M5 button to record.\n");

        if (has_packet)
        {
            tb_display_print_String("Press secondary button to playback.\n");
        }
        printed_wait_msg = true;
    }

    if (M5.BtnA.wasPressed())
    {
        switchState(RECORDING);
        IrReceiver.begin(RECV_PIN);
        tb_display_clear();
        tb_display_print_String("\nWaiting for packet...");
    }
    else if (M5.BtnB.wasPressed())
    {
        // tb_display_print_String("\nB");
        tb_display_print_String((char *)getProtocolString(last_scan.protocol));
    }
}

/* --------------------------------------------------------------------- */
void stateRecording()
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

            memcpy(&last_scan, &IrReceiver.decodedIRData, sizeof(IRData));

            has_packet = true;
            switchState(WAIT);
        }
        IrReceiver.resume();
    }
}

/* --------------------------------------------------------------------- */
void statePlayback()
{
    //
}

/* --------------------------------------------------------------------- */
void loop()
{
    switch (app_state)
    {
    case WAIT:
        stateWait();
        break;
    case RECORDING:
        stateRecording();
        break;
    case PLAYBACK:
        statePlayback();
        break;
    case SCAN:
        break;
    }
}
