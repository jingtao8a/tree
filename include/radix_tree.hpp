#pragma once
#include <stdint.h>

class RadixTree {
private:
    struct RadixNode {
        RadixNode *child[4];
        RadixNode *parent;
        uint32_t value;
    };

private:
    const static uint8_t BIT = 2;
    const static uint8_t RADIXTREEHEIGHT = sizeof(uint32_t) * 8 / BIT;
    RadixNode *root_;
public:
    uint32_t checkBits(uint32_t key, uint8_t pos) {
        return static_cast<uint32_t>((key << sizeof(uint32_t) * 8 - ((pos + 1) * BIT)) >> (sizeof(uint32_t) * 8 - BIT));
    }
};