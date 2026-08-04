#include "ScoreModel.h"

ScoreModel& ScoreModel::instance() {
  static ScoreModel model;
  return model;
}

void ScoreModel::resetPowerOnState() {
  scoreA_ = 0;
  scoreB_ = 0;
  setScoreA_ = cfg::DISPLAY_OFF_VALUE;
  setScoreB_ = cfg::DISPLAY_OFF_VALUE;
}

uint8_t ScoreModel::scoreA() const { return scoreA_; }
uint8_t ScoreModel::scoreB() const { return scoreB_; }
uint8_t ScoreModel::setScoreA() const { return setScoreA_; }
uint8_t ScoreModel::setScoreB() const { return setScoreB_; }

uint8_t ScoreModel::clampIncrement(uint8_t value, uint8_t maxVal) {
  if (value >= maxVal) {
    return maxVal;
  }
  return value + 1;
}

uint8_t ScoreModel::clampDecrement(uint8_t value, uint8_t minVal) {
  if (value <= minVal) {
    return minVal;
  }
  return value - 1;
}

void ScoreModel::incrementScoreA() { scoreA_ = clampIncrement(scoreA_, cfg::SCORE_MAX); }
void ScoreModel::decrementScoreA() { scoreA_ = clampDecrement(scoreA_, cfg::SCORE_MIN); }
void ScoreModel::resetScoreA() { scoreA_ = 0; }

void ScoreModel::incrementScoreB() { scoreB_ = clampIncrement(scoreB_, cfg::SCORE_MAX); }
void ScoreModel::decrementScoreB() { scoreB_ = clampDecrement(scoreB_, cfg::SCORE_MIN); }
void ScoreModel::resetScoreB() { scoreB_ = 0; }

void ScoreModel::incrementSetScoreA() {
  if (setScoreA_ >= cfg::DISPLAY_OFF_VALUE) {
    setScoreA_ = cfg::SET_SCORE_MIN;
    return;
  }
  setScoreA_ = clampIncrement(setScoreA_, cfg::SET_SCORE_MAX);
}

void ScoreModel::decrementSetScoreA() {
  if (setScoreA_ >= cfg::DISPLAY_OFF_VALUE) {
    setScoreA_ = cfg::SET_SCORE_MIN;
    return;
  }
  setScoreA_ = clampDecrement(setScoreA_, cfg::SET_SCORE_MIN);
}

void ScoreModel::resetSetScoreA() { setScoreA_ = cfg::SET_SCORE_MIN; }

void ScoreModel::incrementSetScoreB() {
  if (setScoreB_ >= cfg::DISPLAY_OFF_VALUE) {
    setScoreB_ = cfg::SET_SCORE_MIN;
    return;
  }
  setScoreB_ = clampIncrement(setScoreB_, cfg::SET_SCORE_MAX);
}

void ScoreModel::decrementSetScoreB() {
  if (setScoreB_ >= cfg::DISPLAY_OFF_VALUE) {
    setScoreB_ = cfg::SET_SCORE_MIN;
    return;
  }
  setScoreB_ = clampDecrement(setScoreB_, cfg::SET_SCORE_MIN);
}

void ScoreModel::resetSetScoreB() { setScoreB_ = cfg::SET_SCORE_MIN; }
