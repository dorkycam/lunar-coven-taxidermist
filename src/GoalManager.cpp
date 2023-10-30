#include "GoalManager.h"

#include <Arduino.h>

#include "nft_tags.h"

GoalManager::GoalManager(MFRC522* controller) : nfc(controller) {
}

bool GoalManager::isNewNfcFound() {
    if (!this->nfc->PICC_IsNewCardPresent()) {
        return false;
    }

    Serial.println("card present");
    if (!this->nfc->PICC_ReadCardSerial()) {  // Since a PICC placed get Serial and continue
        return false;
    }

    if (uidEqual(this->nfc->uid.uidByte, lastUid)) {
        return false;
    }

    Serial.println("new card read");
    copyUid(this->nfc->uid.uidByte, this->lastUid);
    this->nfc->PICC_DumpToSerial(&this->nfc->uid);

    printUuid(lastUid);
    return true;
}

bool GoalManager::getFoundFlower() {
    bool isFoundFlower = false;
    for (int i = 0; i < FLOWERS_COUNT; i++) {
        if (uidEqual(FLOWERS[i].rfid, lastUid)) {
            isFoundFlower = true;
            break;
        }
    }

    return isFoundFlower;
}

void GoalManager::printUuid(uint8_t uuid[]) {
    Serial.print("{");
    for (int i = 0; i < 10; i++) {
        Serial.print("0x");
        Serial.print(uuid[i], HEX);
        Serial.print(", ");
    }
    Serial.println("}");
}

bool GoalManager::uidEqual(uint8_t left[], uint8_t right[]) {
    for (int i = 0; i < 10; i++) {
        if (left[i] != right[i]) {
            return false;
        }
    }
    return true;
}

void GoalManager::copyUid(uint8_t from[], uint8_t to[]) {
    for (int i = 0; i < 10; i++) {
        to[i] = from[i];
    }
}