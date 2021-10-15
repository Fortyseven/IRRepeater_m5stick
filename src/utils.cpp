#include <Arduino.h>

char str[255] = ""; // FIXME: hello, overflow

char *toString(int val)
{
    snprintf(str, 255, "0x%x", val);
    return str;
}
