// Struct alignments

#include<stdio.h>

struct bad
{
    u_int32_t a;
    u_int64_t b;
    u_int32_t c;
};

struct good
{
    u_int32_t a;
    u_int32_t c;
    u_int64_t b;
};

struct __attribute__(( __packed__ )) badPacked
{
    u_int32_t a;
    u_int64_t b;
    u_int32_t c;
};

int main(void) {
    printf("%ld bad size\n", sizeof(struct bad));
    printf("%ld good size\n", sizeof(struct good));
    printf("%ld bad packed size\n", sizeof(struct badPacked));
}