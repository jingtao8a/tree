
#include "../include/radix_tree.hpp"
#include <gtest/gtest.h>
#include <vector>

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

TEST(Radix, findDeleteInsert) {
        std::vector<uint32_t> array = {1, 2, 3, 4, 5, 6, 7, 8};
        RadixTree tree;
        for (int key : array) {
                ASSERT_EQ(tree.insert(key, key), 0);
        }
        for (int key: array)
                ASSERT_EQ(tree.find(key), key);
        tree.deleteKey(7);
        tree.deleteKey(8);
        tree.deleteKey(2);
        ASSERT_EQ(tree.find(7), NULL);
        ASSERT_EQ(tree.find(2), NULL);
}