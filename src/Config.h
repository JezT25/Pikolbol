#pragma once

#include <Arduino.h>

namespace cfg {

#ifndef D9
#define D9 3
#endif
#ifndef D10
#define D10 1
#endif

// Data bus pins (D0-D3)
constexpr uint8_t DATA0_PIN = D0;
constexpr uint8_t DATA1_PIN = D1;
constexpr uint8_t DATA2_PIN = D2;
constexpr uint8_t DATA3_PIN = D3;

// Decoder select bits
constexpr uint8_t DECODER_BIT1_PIN = D8;
constexpr uint8_t DECODER_BIT2_PIN = D9;
constexpr uint8_t DECODER_BIT4_PIN = D10;

// Display latch/control pin (must stay HIGH as idle state)
constexpr uint8_t LATCH_PIN = D4;

// Input pins from the wiring image.
constexpr uint8_t SCORE_SWITCH_A_PIN = D5;
constexpr uint8_t SCORE_SWITCH_B_PIN = D6;
constexpr uint8_t SET_SCORE_SWITCH_A_PIN = D7;
constexpr uint8_t SET_SCORE_SWITCH_B_PIN = A0;

// A0 is analog-only on typical NodeMCU boards; treat low ADC values as pressed.
constexpr int ANALOG_BUTTON_PRESSED_THRESHOLD = 200;

// Shared input handling timings
constexpr unsigned long DEBOUNCE_MS = 30;
constexpr unsigned long SHORT_PRESS_MAX_MS = 1000;
constexpr unsigned long LONG_PRESS_MAX_MS = 2000;

// Display protocol timings
constexpr unsigned long DISPLAY_PULSE_LOW_MS = 1;
constexpr unsigned long POST_UPDATE_HOLD_MS = 250;

// Range constraints
constexpr uint8_t SCORE_MIN = 0;
constexpr uint8_t SCORE_MAX = 99;
constexpr uint8_t SET_SCORE_MIN = 0;
constexpr uint8_t SET_SCORE_MAX = 10;
constexpr uint8_t DISPLAY_OFF_VALUE = 10;

// Decoder values (bit4 bit2 bit1 via D10 D9 D8)
constexpr uint8_t DEC_SET_SCORE_A = 0b001;
constexpr uint8_t DEC_SCORE_B_ONES = 0b010;
constexpr uint8_t DEC_SCORE_A_ONES = 0b011;
constexpr uint8_t DEC_SCORE_A_TENS = 0b100;
constexpr uint8_t DEC_SET_SCORE_B = 0b101;
constexpr uint8_t DEC_SCORE_B_TENS = 0b111;

} // namespace cfg
