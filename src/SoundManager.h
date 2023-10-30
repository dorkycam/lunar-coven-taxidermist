#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <Arduino.h>

#define LED_MAX 255
#define LED_MIN 0

#define LED_TWINKLE_MAX 255
#define LED_TWINKLE_MIN 50

class SoundManager {
   public:
    SoundManager(int waitingPin, int flowerPin, int somethingElsePin, int goodbyePin);
    void setupSoundPins();
    void playSound(int pin);
    void startWaitingSound();
    void endWaitingSound();
    void playFlowerSound();
    void playSomethingElseSound();
    void playGoodbyeSound();
    void turnSoundOff();

   private:
    int WAITING_PIN;
    int FLOWER_PIN;
    int SOMETHING_ELSE_PIN;
    int WAITING_DELAY;
    int FLOWER_DELAY;
    int SOMETHING_ELSE_DELAY;
    int GOODBYE_PIN;
    bool isWaitingPlaying;
};

#endif
