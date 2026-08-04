#include "ScoreboardApp.h"

ScoreboardApp& ScoreboardApp::instance() {
  static ScoreboardApp app;
  return app;
}

void ScoreboardApp::begin() {
  controller_.begin();
}

void ScoreboardApp::update() {
  controller_.update();
}
