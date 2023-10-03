#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

int main() {
    FILE *fp = fopen("/home/jingtao8a/tree/test/operation.txt", "w");
    assert(fp);
    srand(time(NULL));
    
    for (int i = 0; i < 1000; ++i) {
        int key = rand() % 20000;
        int op = rand() % 2;
        switch (op) {
            case 0:
                fprintf(fp, "insert %d\n", key);
                break;
            case 1:
                fprintf(fp, "remove %d\n", key);
                break;
        }
    }
    fclose(fp);
}