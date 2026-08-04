#pragma once

#include <Arduino.h>
#include "Config.h"

class ScoreModel {
public:
  static ScoreModel& instance();

  void resetPowerOnState();

  uint8_t scoreA() const;
  uint8_t scoreB() const;
  uint8_t setScoreA() const;
  uint8_t setScoreB() const;

  void incrementScoreA();
  void decrementScoreA();
  void resetScoreA();

  void incrementScoreB();
  void decrementScoreB();
  void resetScoreB();

  void incrementSetScoreA();
  void decrementSetScoreA();
  void resetSetScoreA();

  void incrementSetScoreB();
  void decrementSetScoreB();
  void resetSetScoreB();

private:
  ScoreModel() = default;

  uint8_t scoreA_ = 0;
  uint8_t scoreB_ = 0;
  uint8_t setScoreA_ = cfg::DISPLAY_OFF_VALUE;
  uint8_t setScoreB_ = cfg::DISPLAY_OFF_VALUE;

  uint8_t clampIncrement(uint8_t value, uint8_t maxVal);
  uint8_t clampDecrement(uint8_t value, uint8_t minVal);
};
