#include "radix_tree.hpp"

int RadixTree::insert(uint32_t key, uint32_t value) {
    RadixNode *node = root_;
    uint32_t temp;
    for (int i = 0; i < RADIXTREEHEIGHT; ++i) {
        temp = checkBits(key, i);
        if (!node->child[temp]) {
            node->child[temp] = new RadixNode();
            node->child[temp]->parent = node;
        }
        node = node->child[temp];
    }
    if (node->value == value) return RADIX_INSERT_VALUE_SAME;
    if (node->value) return RADIX_INSERT_VALUE_OCCUPY;
    node->value = value;
    return 0;
}

int RadixTree::deleteKey(uint32_t key) {
    RadixNode *node = root_;
    int temp;
    for (int i = 0; node != NULL && i < RADIXTREEHEIGHT; ++i) {
        temp = checkBits(key, i);
        node = node->child[temp];
    }
    if (node == NULL) return RADIX_DELETE_ERROR;
    RadixNode *parent = node->parent;
    parent->child[temp] = NULL;
    delete node;
    return 0;
}

uint32_t RadixTree::find(uint32_t key) {
    int temp;
    RadixNode *node = root_;
    for (int i = 0; node != NULL && i < RADIXTREEHEIGHT; ++i) {
        temp = checkBits(key, i);
        node = node->child[temp];
    }
    if (node == NULL) return 0;
    return node->value;
}