
#ifndef nft_tags_H
#define nft_tags_H 1

#include <Arduino.h>

#define FLOWERS_COUNT 60

// FLOWER NFC TAGS
struct Flower {
    uint8_t rfid[10];
};

extern Flower FLOWERS[FLOWERS_COUNT];

#endif
