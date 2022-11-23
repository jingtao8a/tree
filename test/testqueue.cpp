#include <iostream>
#include <queue>


int main() {
    std::queue<int> que;
    for (int i = 0; i < 10; ++i) {
        que.push(i);
    }
    std::cout << que.front();
    return 0;
}