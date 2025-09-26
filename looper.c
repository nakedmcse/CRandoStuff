// Forever looping
#include<stdio.h>
#include<string.h>

typedef struct looper {
    char *s;
    int i;
    char (*next)(void *);
} looper;

char next(void *l) {
    looper *lp = (looper *)l;
    int c = lp->i;
    lp->i = (lp->i + 1) % (int)strlen(lp->s);
    return lp->s[c];
}

int main(void) {
    looper l1 = {"abc", 0, next};
    looper l2 = {"def", 0, next};

    printf("%c\n", l1.next(&l1));
    printf("%c\n", l1.next(&l1));
    printf("%c\n", l1.next(&l1));
    printf("%c\n", l1.next(&l1));

    printf("%c\n", l2.next(&l2));
    printf("%c\n", l2.next(&l2));
    printf("%c\n", l2.next(&l2));
    printf("%c\n", l2.next(&l2));

    return 0;
}