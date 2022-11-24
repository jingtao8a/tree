#include "../include/avl_tree.hpp"
#include <stdio.h>
#include <string.h>
#include <iostream>

static char buffer[1024];
int main() {
    AVLTree tree;
    AVLTree::Key_t key;
    AVLTree::Value_t value;
    freopen("/home/yuxintao/tree/test/operation.txt", "r", stdin);
    freopen("./log.txt", "w", stdout);
    while (true) {
        memset(buffer, 0, 1024);
        if (fgets(buffer, 1024, stdin) == NULL) {
            if (feof(stdin)) {
                break;
            }
        }
        int ret = 0;
        ret = sscanf(buffer, "insert %d", &key.key);
        if (ret == 1) {
            std::cout << "insert " << key.key << std::endl;
            tree.insert(key, value);
            tree.print();
            continue;
        }

        ret = sscanf(buffer, "remove %d", &key.key);
        if (ret == 1) {
            std::cout << "remove " << key.key << std::endl;
            tree.remove(key);
            tree.print();
            continue;
        }
    }
    return 0;
}