#pragma once

#include <Arduino.h>
#include <IRremoteInt.h>

#define STATE_WAIT 0
#define STATE_RECORDING 1
#define STATE_PLAYBACK 2
#define STATE_SCAN 3

#define IR_RECV_PIN 26

extern bool has_scan;
extern IRData last_scan;
extern uint8_t last_raw[100];

// utils

extern char *toString(int val);

extern void dumpBytes(uint16_t *shit, int shitlen);

extern void setBanner(
    char *banner_text,
    uint32_t clear_color,
    uint32_t background_color,
    uint32_t text_color);