#include "ScoreController.h"

ScoreController::ScoreController()
  : scoreAButton_(
      cfg::SCORE_SWITCH_A_PIN,
      false,
      cfg::DIGITAL_SWITCH_USE_INTERNAL_PULLUP,
      cfg::DIGITAL_SWITCH_ACTIVE_LOW),
    scoreBButton_(
      cfg::SCORE_SWITCH_B_PIN,
      false,
      cfg::DIGITAL_SWITCH_USE_INTERNAL_PULLUP,
      cfg::DIGITAL_SWITCH_ACTIVE_LOW),
    setScoreAButton_(
      cfg::SET_SCORE_SWITCH_A_PIN,
      false,
      cfg::DIGITAL_SWITCH_USE_INTERNAL_PULLUP,
      cfg::DIGITAL_SWITCH_ACTIVE_LOW),
    setScoreBButton_(
      cfg::SET_SCORE_SWITCH_B_PIN,
      cfg::SET_SCORE_B_USE_ANALOG,
      cfg::DIGITAL_SWITCH_USE_INTERNAL_PULLUP,
      cfg::DIGITAL_SWITCH_ACTIVE_LOW),
      model_(ScoreModel::instance()),
      display_(DisplayDriver::instance()) {}

ScoreController& ScoreController::instance() {
  static ScoreController controller;
  return controller;
}

void ScoreController::begin() {
  display_.begin();

  scoreAButton_.begin();
  scoreBButton_.begin();
  setScoreAButton_.begin();
  setScoreBButton_.begin();

  model_.resetPowerOnState();
  refreshDisplay();
}

void ScoreController::refreshDisplay() {
  display_.drawAll(model_.scoreA(), model_.scoreB(), model_.setScoreA(), model_.setScoreB());
}

void ScoreController::applyPostDisplayHold(PressType press, const ButtonInput& sourceButton) {
  if (press == PressType::Short) {
    display_.holdShortPress();
  } else if (press == PressType::Medium) {
    display_.holdMediumPress();
  } else if (press == PressType::Long) {
    display_.holdUntilReleased(sourceButton.pin(), sourceButton.isAnalogMode());
  }
}

void ScoreController::handleScoreAPress(PressType press) {
  if (press == PressType::Short) {
    model_.incrementScoreA();
  } else if (press == PressType::Medium) {
    model_.decrementScoreA();
  } else if (press == PressType::Long) {
    model_.resetScoreA();
  } else {
    return;
  }

  refreshDisplay();
  applyPostDisplayHold(press, scoreAButton_);
}

void ScoreController::handleScoreBPress(PressType press) {
  if (press == PressType::Short) {
    model_.incrementScoreB();
  } else if (press == PressType::Medium) {
    model_.decrementScoreB();
  } else if (press == PressType::Long) {
    model_.resetScoreB();
  } else {
    return;
  }

  refreshDisplay();
  applyPostDisplayHold(press, scoreBButton_);
}

void ScoreController::handleSetScoreAPress(PressType press) {
  if (press == PressType::Short) {
    model_.incrementSetScoreA();
  } else if (press == PressType::Medium) {
    model_.decrementSetScoreA();
  } else if (press == PressType::Long) {
    model_.resetSetScoreA();
  } else {
    return;
  }

  refreshDisplay();
  applyPostDisplayHold(press, setScoreAButton_);
}

void ScoreController::handleSetScoreBPress(PressType press) {
  if (press == PressType::Short) {
    model_.incrementSetScoreB();
  } else if (press == PressType::Medium) {
    model_.decrementSetScoreB();
  } else if (press == PressType::Long) {
    model_.resetSetScoreB();
  } else {
    return;
  }

  refreshDisplay();
  applyPostDisplayHold(press, setScoreBButton_);
}

void ScoreController::update() {
  handleScoreAPress(scoreAButton_.poll());
  handleScoreBPress(scoreBButton_.poll());
  handleSetScoreAPress(setScoreAButton_.poll());
  handleSetScoreBPress(setScoreBButton_.poll());
}
