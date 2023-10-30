
#ifndef GOAL_MANAGER_H
#define GOAL_MANAGER_H

#include <Arduino.h>
#include <MFRC522.h>

class GoalManager {
   public:
    GoalManager(MFRC522* controller);
    void printUuid(uint8_t uuid[]);
    bool uidEqual(uint8_t left[], uint8_t right[]);
    void copyUid(uint8_t from[], uint8_t to[]);
    bool getFoundFlower();
    bool isNewNfcFound();

   private:
    MFRC522* nfc;
    uint8_t lastUid[10];
};

#endif
