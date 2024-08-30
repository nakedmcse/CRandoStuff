//  String Int Multiplier
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<gmp.h>

char *stringMult(const char *a, const char *b) {
    char *end;
    char buf[21];
    long act_a = strtol(a, &end, 10);
    long act_b = strtol(b, &end, 10);
    sprintf(buf, "%ld", (act_a*act_b));
    char *retval = (char *)malloc(strlen(buf));
    strcpy(retval, buf);
    return retval;
}

char *stringMultArb(const char *a, const char *b) {
    mpz_t act_a, act_b, act_mul;
    mpz_init(act_mul);
    mpz_init_set_str(act_a, a, 10);
    mpz_init_set_str(act_b, b, 10);
    mpz_mul(act_mul, act_a, act_b);
    char *retval = mpz_get_str(NULL, 10, act_mul);
    mpz_clear(act_a);
    mpz_clear(act_b);
    mpz_clear(act_mul);
    return retval;
}

int main(void) {
    printf("%s\n",stringMult("10","100"));
    printf("%s\n",stringMult("65535", "65535"));
    printf("%s\n",stringMult("2147483647", "2147483647"));
    printf("%s\n",stringMultArb("1844674407370955161501234","1844674407370955161501234"));
}