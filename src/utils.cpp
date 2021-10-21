#include <Arduino.h>
#include <IRremoteInt.h>
#include <M5StickC.h>

/* -------------------------------------------- */
char str[255] = ""; // FIXME: hello, overflow

char *toString(int val)
{
    snprintf(str, 255, "0x%x", val);
    return str;
}

/* -------------------------------------------- */
void dumpIRData(HardwareSerial *serial, IRData *irdata)
{
    serial->println("-------------- IRData dump");
    serial->printf("Protocol:   %s\n", getProtocolString(irdata->protocol));
    serial->printf("Address:    0x%x\n", irdata->address);
    serial->printf("Command:    0x%x\n", irdata->command);
    serial->printf("Extra:      0x%x\n", irdata->extra);
    serial->printf("Bits:       0x%x\n", irdata->numberOfBits);
    serial->printf("decodedRaw: 0x%x\n", irdata->decodedRawData);
}

/* -------------------------------------------- */
void setBanner(
    char *banner_text,
    uint32_t clear_color,
    uint32_t background_color,
    uint32_t text_color)
{
    unsigned int width = M5.Lcd.width();
    unsigned int msg_offset = (strlen(banner_text) / 2) * 8;

    M5.Lcd.fillScreen(clear_color);
    M5.Lcd.fillRect(0, 0, width, 8, background_color);
    M5.Lcd.setTextColor(text_color);
    M5.Lcd.setCursor(
        (width / 2) - msg_offset,
        0);
    M5.Lcd.println(banner_text);
    M5.Lcd.setCursor(0, 8);
}