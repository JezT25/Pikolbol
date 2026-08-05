#pragma once

#include <Arduino.h>
#include "Config.h"

enum class PressType : uint8_t {
  None,
  Short,
  Medium,
  Long
};

class ButtonInput {
public:
  explicit ButtonInput(
      uint8_t pin,
      bool analogMode = false,
      bool useInternalPullup = true,
      bool activeLow = true);

  void begin();
  PressType poll();
  uint8_t pin() const;
  bool isAnalogMode() const;

private:
  bool readPressedRaw() const;

  uint8_t pin_;
  bool analogMode_;
  bool useInternalPullup_;
  bool activeLow_;
  bool lastRawState_;
  bool stablePressed_;
  bool longPressFired_;
  unsigned long lastDebounceAtMs_;
  unsigned long pressedAtMs_;
};
