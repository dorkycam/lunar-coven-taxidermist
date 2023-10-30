#include "LedManager.h"

LedManager::LedManager(int neckPin, int nosePin, int rightEyePin, int leftEyePin) {
    NECK_PIN = neckPin;
    NOSE_PIN = nosePin;
    RIGHT_EYE_PIN = rightEyePin;
    LEFT_EYE_PIN = leftEyePin;
}

void LedManager::setupLights() {
  pinMode(NECK_PIN, OUTPUT);
  digitalWrite(NECK_PIN, LED_MIN); 
   pinMode(NOSE_PIN, OUTPUT);
  digitalWrite(NOSE_PIN, 100); 
   pinMode(RIGHT_EYE_PIN, OUTPUT);
  digitalWrite(RIGHT_EYE_PIN, 100); 
   pinMode(LEFT_EYE_PIN, OUTPUT);
  digitalWrite(LEFT_EYE_PIN, 100);
}

void LedManager::turnOnLight(int pin, uint8_t brightness) {
    digitalWrite(pin, LED_MAX);
}

void LedManager::turnOffLight(int pin) {
    this->turnOnLight(pin, LED_MIN);
}

void LedManager::setAllLightsBrightness(uint8_t brightness) {
    // this->turnOnLight(this->NECK_PIN, brightness);
    this->turnOnLight(this->NOSE_PIN, brightness);
    this->turnOnLight(this->RIGHT_EYE_PIN, brightness);
    this->turnOnLight(this->LEFT_EYE_PIN, brightness);
}

void LedManager::fadeAllOut(float seconds) {
    Serial.println("fadeAllOut");
    this->setAllLightsBrightness(LED_MAX);
    unsigned long start = millis();
    unsigned long end = start + (seconds * 1000);
    unsigned long total = end - start;
    unsigned long now = millis();
    do {
        float pct = (float)(end - now) / (float)total;
        int val = (LED_MAX * pct);
        this->setAllLightsBrightness(val);
        now = millis();
    } while (now < end);
}

void LedManager::fadeOneOut(float seconds, int goalNum) {
    Serial.println("fadeAllOut");
    this->turnOnLight(goalNum, LED_MAX);
    unsigned long start = millis();
    unsigned long end = start + (seconds * 1000);
    unsigned long total = end - start;
    unsigned long now = millis();
    do {
        float pct = (float)(end - now) / (float)total;
        int val = (LED_MAX * pct);
        this->turnOnLight(goalNum, val);
        now = millis();
    } while (now < end);
}

void LedManager::fadeAllIn(float seconds, int startBrightness, int endBrightness) {
    Serial.println("fadeAllIn");
    this->setAllLightsBrightness(startBrightness);
    unsigned long start = millis();
    unsigned long end = start + (seconds * 1000);
    unsigned long total = end - start;
    unsigned long now = millis();
    do {
        float pct = (float)(end - now) / (float)total;
        int val = endBrightness - (endBrightness * pct);
        this->setAllLightsBrightness(val);
        now = millis();
    } while (now < end);
}

void LedManager::fadeOneIn(float seconds, int goalNum) {
    Serial.println("fadeOneIn");
    this->turnOnLight(goalNum, LED_MIN);
    unsigned long start = millis();
    unsigned long end = start + (seconds * 1000);
    unsigned long total = end - start;
    unsigned long now = millis();
    do {
        float pct = (float)(end - now) / (float)total;
        int val = (LED_MAX * pct);
        this->turnOnLight(goalNum, val);
        now = millis();
    } while (now < end);
}

void LedManager::fade(float seconds, int pin, int startBrightness, int endBrightness) {
    Serial.println("fade");
    this->turnOnLight(pin, startBrightness);
    unsigned long start = millis();
    unsigned long end = start + (seconds * 1000);
    unsigned long total = end - start;
    unsigned long now = millis();
    do {
        float pct = (float)(end - now) / (float)total;
        int val = (endBrightness * pct);
        this->turnOnLight(pin, val);
        now = millis();
    } while (now < end);
}

void LedManager::startFlowerAnimation() {
    fadeAllIn(3, 100, LED_MAX);
    fade(3, NECK_PIN, LED_MIN, LED_MAX);
}

void LedManager::endFlowerAnimation() {
    fadeAllIn(3, LED_MAX, 100);
    fade(3, NECK_PIN, LED_MAX, LED_MIN);
}