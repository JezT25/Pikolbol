#pragma once

#include "ScoreController.h"

class ScoreboardApp {
public:
  static ScoreboardApp& instance();

  void begin();
  void update();

private:
  ScoreboardApp() = default;
  ScoreController& controller_ = ScoreController::instance();
};
