// Stupid string copy
#include<stdio.h>

void bakaCopy(char *to, char *from, size_t count) {
    size_t n = (count + 7) / 8;

    switch (count % 8) {
        case 0: printf("Case 0 copy\n"); do {
            *to++ = *from++;
            case 7: printf("Case 7 copy\n"); *to++ = *from++;
            case 6: printf("Case 6 copy\n"); *to++ = *from++;
            case 5: printf("Case 5 copy\n"); *to++ = *from++;
            case 4: printf("Case 4 copy\n"); *to++ = *from++;
            case 3: printf("Case 3 copy\n"); *to++ = *from++;
            case 2: printf("Case 2 copy\n"); *to++ = *from++;
            case 1: printf("Case 1 copy\n"); *to++ = *from++;
        } while (--n > 0);
    }
}

int main(void) {
    static char source[18] = "This is the source";
    static char target[18] = "                  ";

    bakaCopy(&target[0], &source[0], 18);

    printf("Source: %s \nTarget: %s \n", source, target);
}