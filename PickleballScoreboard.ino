#include "src/ScoreboardApp.h"

ScoreboardApp& app = ScoreboardApp::instance();

void setup() {
  app.begin();
}

void loop() {
  app.update();
}
