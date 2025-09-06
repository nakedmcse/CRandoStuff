// Yield in C
#include <stdio.h>

int yieldLoop(void) {
    static int i, yieldState = 0;
    switch (yieldState) {
        case 0:
            for (i = 0; i < 5; i++) {
                yieldState = 1;
                return i;
                case 1:;
            }
    }
}

int main(void) {
    printf("%d\n", yieldLoop());  // 0
    printf("%d\n", yieldLoop());  // 1
    printf("%d\n", yieldLoop());  // 2
    printf("%d\n", yieldLoop());  // 3
    printf("%d\n", yieldLoop());  // 4
}
