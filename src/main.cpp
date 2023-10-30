
#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>

#include "GoalManager.h"
#include "LedManager.h"
#include "SoundManager.h"
#include "nft_tags.h"

#define AUDIO_PIN_WAITING 4
#define AUDIO_PIN_WRONG_ITEM 3
#define AUDIO_PIN_RIGHT_ITEM 2
#define AUDIO_PIN_GOODBYE 5
#define AUDIO_RESET_PIN 8

#define LED_PIN_NECK 14
#define LED_PIN_NOSE 15
#define LED_PIN_RIGHT_EYE 16
#define LED_PIN_LEFT_EYE 17

// for RFID scanner driver setup
MFRC522 mfrc522(10, 9);

LedManager ledManager(LED_PIN_NECK, LED_PIN_NOSE, LED_PIN_RIGHT_EYE, LED_PIN_LEFT_EYE);
GoalManager goalManager(&mfrc522);
SoundManager soundManager(AUDIO_PIN_WAITING, AUDIO_PIN_RIGHT_ITEM, AUDIO_PIN_WRONG_ITEM, AUDIO_PIN_GOODBYE);

void setup() {
    Serial.begin(9600);
    while (!Serial)
        delay(1);  // wait for serial port to open

    Serial.println("beginning");

    // RFID SETUP
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("rfc works");
    // RFID scanner pin setup
    pinMode(7, OUTPUT);

    // LED SETUP
    ledManager.setupLights();

    // SOUND SETUP
    soundManager.setupSoundPins();
    // soundManager.startWaitingSound(); // start playing right away

    Serial.println("Setup complete! (but check for errors)");
}

void loop() {
    soundManager.startWaitingSound();

    if (!goalManager.isNewNfcFound()) {
        return;
    }

    // they scanned something
    if (goalManager.getFoundFlower()) {
        Serial.println("Scanned flower!");
        ledManager.turnOnLight(LED_PIN_NECK, LED_MAX);
        soundManager.endWaitingSound();
        soundManager.playFlowerSound();
        delay(24000);
        digitalWrite(LED_PIN_NECK, 0);
        soundManager.playGoodbyeSound();
        delay(5500);
        return;
    }

    Serial.println("Scanned something else!");
    soundManager.endWaitingSound();
    soundManager.playSomethingElseSound();
    delay(6000);
}