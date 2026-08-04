#include "DisplayDriver.h"

DisplayDriver& DisplayDriver::instance() {
  static DisplayDriver driver;
  return driver;
}

void DisplayDriver::begin() {
  pinMode(cfg::DATA0_PIN, OUTPUT);
  pinMode(cfg::DATA1_PIN, OUTPUT);
  pinMode(cfg::DATA2_PIN, OUTPUT);
  pinMode(cfg::DATA3_PIN, OUTPUT);

  pinMode(cfg::DECODER_BIT1_PIN, OUTPUT);
  pinMode(cfg::DECODER_BIT2_PIN, OUTPUT);
  pinMode(cfg::DECODER_BIT4_PIN, OUTPUT);

  pinMode(cfg::LATCH_PIN, OUTPUT);
  setLatchHighIdle();
}

void DisplayDriver::setDataBus(uint8_t value) {
  digitalWrite(cfg::DATA0_PIN, (value >> 0) & 0x01);
  digitalWrite(cfg::DATA1_PIN, (value >> 1) & 0x01);
  digitalWrite(cfg::DATA2_PIN, (value >> 2) & 0x01);
  digitalWrite(cfg::DATA3_PIN, (value >> 3) & 0x01);
}

void DisplayDriver::setDecoder(uint8_t decoderValue) {
  digitalWrite(cfg::DECODER_BIT1_PIN, (decoderValue & 0x01) ? HIGH : LOW);
  digitalWrite(cfg::DECODER_BIT2_PIN, (decoderValue & 0x02) ? HIGH : LOW);
  digitalWrite(cfg::DECODER_BIT4_PIN, (decoderValue & 0x04) ? HIGH : LOW);
}

void DisplayDriver::setLatchHighIdle() {
  digitalWrite(cfg::LATCH_PIN, HIGH);
}

void DisplayDriver::pushDigit(uint8_t decoderValue, uint8_t digitValue) {
  // Protocol: keep latch HIGH, set data/decoder, pulse LOW for 1 ms, return HIGH.
  setLatchHighIdle();
  setDataBus(digitValue);
  setDecoder(decoderValue);
  digitalWrite(cfg::LATCH_PIN, LOW);
  delay(cfg::DISPLAY_PULSE_LOW_MS);
  setLatchHighIdle();
}

void DisplayDriver::drawAll(uint8_t scoreA, uint8_t scoreB, uint8_t setScoreA, uint8_t setScoreB) {
  const uint8_t scoreATens = scoreA / 10;
  const uint8_t scoreAOnes = scoreA % 10;
  const uint8_t scoreBTens = scoreB / 10;
  const uint8_t scoreBOnes = scoreB % 10;

  // Order is explicit to keep behavior deterministic.
  pushDigit(cfg::DEC_SET_SCORE_A, setScoreA);
  pushDigit(cfg::DEC_SCORE_B_ONES, scoreBOnes);
  pushDigit(cfg::DEC_SCORE_A_ONES, scoreAOnes);
  pushDigit(cfg::DEC_SCORE_A_TENS, scoreATens);
  pushDigit(cfg::DEC_SET_SCORE_B, setScoreB);
  pushDigit(cfg::DEC_SCORE_B_TENS, scoreBTens);
}

void DisplayDriver::holdShortPress() {
  digitalWrite(cfg::LATCH_PIN, LOW);
  delay(cfg::POST_UPDATE_HOLD_MS);
  setLatchHighIdle();
}

void DisplayDriver::holdMediumPress() {
  digitalWrite(cfg::LATCH_PIN, LOW);
  delay(cfg::POST_UPDATE_HOLD_MS);
  setLatchHighIdle();
  delay(cfg::POST_UPDATE_HOLD_MS);
  digitalWrite(cfg::LATCH_PIN, LOW);
  delay(cfg::POST_UPDATE_HOLD_MS);
  setLatchHighIdle();
}

void DisplayDriver::holdUntilReleased(uint8_t releasePin, bool analogRelease) {
  digitalWrite(cfg::LATCH_PIN, LOW);
  while (true) {
    const bool stillPressed = analogRelease
        ? (analogRead(releasePin) <= cfg::ANALOG_BUTTON_PRESSED_THRESHOLD)
        : (digitalRead(releasePin) == LOW);

    if (!stillPressed) {
      break;
    }
    delay(5);
  }
  setLatchHighIdle();
}
