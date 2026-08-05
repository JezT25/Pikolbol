#include "ButtonInput.h"

ButtonInput::ButtonInput(uint8_t pin, bool analogMode, bool useInternalPullup, bool activeLow)
    : pin_(pin),
      analogMode_(analogMode),
      useInternalPullup_(useInternalPullup),
      activeLow_(activeLow),
      lastRawState_(HIGH),
      stablePressed_(false),
      longPressFired_(false),
      lastDebounceAtMs_(0),
      pressedAtMs_(0) {}

void ButtonInput::begin() {
  if (!analogMode_) {
    pinMode(pin_, useInternalPullup_ ? INPUT_PULLUP : INPUT);
  }
  lastRawState_ = readPressedRaw();
  stablePressed_ = lastRawState_;
}

bool ButtonInput::readPressedRaw() const {
  if (analogMode_) {
    return analogRead(pin_) <= cfg::ANALOG_BUTTON_PRESSED_THRESHOLD;
  }
  const int rawLevel = digitalRead(pin_);
  return activeLow_ ? (rawLevel == LOW) : (rawLevel == HIGH);
}

PressType ButtonInput::poll() {
  const bool rawPressed = readPressedRaw();

  if (rawPressed != lastRawState_) {
    lastDebounceAtMs_ = millis();
    lastRawState_ = rawPressed;
  }

  if ((millis() - lastDebounceAtMs_) < cfg::DEBOUNCE_MS) {
    return PressType::None;
  }

  if (rawPressed && !stablePressed_) {
    stablePressed_ = true;
    longPressFired_ = false;
    pressedAtMs_ = millis();
    return PressType::None;
  }

  if (rawPressed && stablePressed_ && !longPressFired_) {
    const unsigned long heldMs = millis() - pressedAtMs_;
    if (heldMs > cfg::LONG_PRESS_MAX_MS) {
      longPressFired_ = true;
      return PressType::Long;
    }
  }

  if (!rawPressed && stablePressed_) {
    stablePressed_ = false;

    if (longPressFired_) {
      longPressFired_ = false;
      return PressType::None;
    }

    const unsigned long heldMs = millis() - pressedAtMs_;

    if (heldMs > cfg::SHORT_PRESS_MAX_MS) {
      return PressType::Medium;
    }
    return PressType::Short;
  }

  return PressType::None;
}

uint8_t ButtonInput::pin() const {
  return pin_;
}

bool ButtonInput::isAnalogMode() const {
  return analogMode_;
}
