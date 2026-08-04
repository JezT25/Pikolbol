#pragma once

#include <Arduino.h>
#include "Config.h"

class DisplayDriver {
public:
  static DisplayDriver& instance();

  void begin();

  // Draw complete scoreboard state.
  void drawAll(uint8_t scoreA, uint8_t scoreB, uint8_t setScoreA, uint8_t setScoreB);

  // Post-action hold behavior from the specification.
  void holdShortPress();
  void holdMediumPress();
  void holdUntilReleased(uint8_t releasePin, bool analogRelease = false);

private:
  DisplayDriver() = default;

  void setDataBus(uint8_t value);
  void setDecoder(uint8_t decoderValue);
  void pushDigit(uint8_t decoderValue, uint8_t digitValue);
  void setLatchHighIdle();
};
