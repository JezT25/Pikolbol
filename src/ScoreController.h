#pragma once

#include "ButtonInput.h"
#include "DisplayDriver.h"
#include "ScoreModel.h"

class ScoreController {
public:
  static ScoreController& instance();

  void begin();
  void update();

private:
  ScoreController();

  ButtonInput scoreAButton_;
  ButtonInput scoreBButton_;
  ButtonInput setScoreAButton_;
  ButtonInput setScoreBButton_;

  ScoreModel& model_;
  DisplayDriver& display_;

  void refreshDisplay();

  void handleScoreAPress(PressType press);
  void handleScoreBPress(PressType press);
  void handleSetScoreAPress(PressType press);
  void handleSetScoreBPress(PressType press);

  void applyPostDisplayHold(PressType press, const ButtonInput& sourceButton);
};
