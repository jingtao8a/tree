#pragma once
#include <stdint.h>
#include <string.h>

class RadixTree {
public:
    enum {
        RADIX_INSERT_VALUE_SAME = 1,
        RADIX_INSERT_VALUE_OCCUPY = 2,
        RADIX_DELETE_ERROR = 3,
    };
private:
    struct RadixNode {
        RadixNode *child[4];
        RadixNode *parent = nullptr;
        uint32_t value = 0;
        RadixNode() {
            memset(child, 0, sizeof(child));
        }
    };

private:
    const static uint8_t BIT = 2;
    const static uint8_t RADIXTREEHEIGHT = sizeof(uint32_t) * 8 / BIT;
    RadixNode *root_;
public:
    RadixTree() {
        root_ = new RadixNode(); 
    }
    uint32_t checkBits(uint32_t key, uint8_t pos) {
        return static_cast<uint32_t>((key << sizeof(uint32_t) * 8 - ((pos + 1) * BIT)) >> (sizeof(uint32_t) * 8 - BIT));
    }

    int insert(uint32_t key, uint32_t value);
    int deleteKey(uint32_t key);
    uint32_t find(uint32_t key);
};