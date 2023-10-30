#include "SoundManager.h"

#include <Arduino.h>
#include <SPI.h>

SoundManager::SoundManager(int waitingPin, int flowerPin, int somethingElsePin, int goodbyePin) {
    WAITING_PIN = waitingPin;
    FLOWER_PIN = flowerPin;
    SOMETHING_ELSE_PIN = somethingElsePin;
    GOODBYE_PIN = goodbyePin;
    isWaitingPlaying = false;
}

void SoundManager::setupSoundPins() {
    pinMode(WAITING_PIN, OUTPUT);
    digitalWrite(WAITING_PIN, HIGH);

    pinMode(FLOWER_PIN, OUTPUT);
    digitalWrite(FLOWER_PIN, HIGH);

    pinMode(SOMETHING_ELSE_PIN, OUTPUT);
    digitalWrite(SOMETHING_ELSE_PIN, HIGH);

    pinMode(GOODBYE_PIN, OUTPUT);
    digitalWrite(GOODBYE_PIN, HIGH);
};

void SoundManager::playSound(int pin) {
    // turn current sound off
    turnSoundOff();
    Serial.println("sound");
    digitalWrite(pin, LOW); // bring the pin low to begin the activation
    delay(250); // hold the pin low long enough to trigger the board; may need to be longer for consistent triggering
    digitalWrite(pin, HIGH); // bring the pin high again to end the activation
};

void SoundManager::startWaitingSound() {
    if (isWaitingPlaying) {
        // Serial.println("waiting already playing");
        return;
    }
    isWaitingPlaying = true;
    playSound(WAITING_PIN);
};

void SoundManager::endWaitingSound() {
    if (!isWaitingPlaying) {
        // Serial.println("waiting already off");
        return;
    }
    isWaitingPlaying = false;
    playSound(WAITING_PIN);
};

void SoundManager::playFlowerSound() {
    playSound(FLOWER_PIN);
};

void SoundManager::playSomethingElseSound() {
    playSound(SOMETHING_ELSE_PIN);
};

void SoundManager::playGoodbyeSound() {
    playSound(GOODBYE_PIN);
};

void SoundManager::turnSoundOff() {
    // digitalWrite(WAITING_PIN, HIGH);
    digitalWrite(FLOWER_PIN, HIGH);
    digitalWrite(SOMETHING_ELSE_PIN, HIGH);
};