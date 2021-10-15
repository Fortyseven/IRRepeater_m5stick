#pragma once

#include <Arduino.h>
#include <IRremoteInt.h>

#define STATE_WAIT 0
#define STATE_RECORDING 1
#define STATE_PLAYBACK 2
#define STATE_SCAN 3

#define IR_RECV_PIN 26

extern IRData last_scan;

extern char *toString(int val);
