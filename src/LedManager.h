#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include <Arduino.h>

#define LED_MAX 255
#define LED_MIN 0

#define LED_TWINKLE_MAX 255
#define LED_TWINKLE_MIN 50

class LedManager {
   public:
    LedManager(int neckPin, int nosePin, int rightEyePin, int leftEyePin);
    void setupLights();
    void turnOnLight(int pinNum, uint8_t brightness = LED_MAX);
    void turnOffLight(int pinNum);
    void setAllLightsBrightness(uint8_t brightness = LED_MAX);
    void startFlowerAnimation();
    void endFlowerAnimation();
    void fade(float seconds, int pin, int startBrightness, int endBrightness);

    void fadeAllOut(float seconds);
    void fadeOneOut(float seconds, int pineNum);
    void fadeAllIn(float seconds, int startBrightness, int endBrightness);
    void fadeOneIn(float seconds, int pineNum);

   private:
    int NECK_PIN;
    int NOSE_PIN;
    int RIGHT_EYE_PIN;
    int LEFT_EYE_PIN;
};

#endif
