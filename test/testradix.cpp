
#include "../include/radix_tree.hpp"
#include <gtest/gtest.h>

TEST(Radix, checkBits) {
        uint32_t key = 0x12345678;
        RadixTree tree;
        
        ASSERT_EQ(tree.checkBits(key, 0), 0);
        ASSERT_EQ(tree.checkBits(key, 1), 2);
        ASSERT_EQ(tree.checkBits(key, 2), 3);
        ASSERT_EQ(tree.checkBits(key, 3), 1);
        ASSERT_EQ(tree.checkBits(key, 4), 2);
        ASSERT_EQ(tree.checkBits(key, 5), 1);
        ASSERT_EQ(tree.checkBits(key, 6), 1);
        ASSERT_EQ(tree.checkBits(key, 7), 1);
        ASSERT_EQ(tree.checkBits(key, 8), 0);
}