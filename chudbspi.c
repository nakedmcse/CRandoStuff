// Chudnovsky approximation of Pi with binary splitting
#include <stdio.h>
#include <time.h>
#include <math.h>
#include </opt/homebrew/include/gmp.h>

typedef struct {
    mpz_t pab, qab, tab;
} result;

result bs(mpz_t a, mpz_t b, mpz_t c3) {
    result res, resLow, resHigh;
    mpz_t diff, tmp, tmp2;
    mpz_init(res.pab);
    mpz_init(res.qab);
    mpz_init(res.tab);
    mpz_init(resLow.pab);
    mpz_init(resLow.qab);
    mpz_init(resLow.tab);
    mpz_init(resHigh.pab);
    mpz_init(resHigh.qab);
    mpz_init(resHigh.tab);
    mpz_init(diff);
    mpz_init(tmp);
    mpz_init(tmp2);

    mpz_sub(diff, a, b);

    if (mpz_get_ui(diff) == 1) {
        if (mpz_get_ui(a) == 0) {
            mpz_set_ui(res.pab, 1UL);
            mpz_set_ui(res.qab, 1UL);
        } else {
            // tmp  = 6a - 5
            mpz_mul_ui(tmp, a, 6UL);
            mpz_sub_ui(tmp, tmp, 5UL);

            // tmp2 = 2a - 1
            mpz_mul_ui(tmp2, a, 2UL);
            mpz_sub_ui(tmp2, tmp2, 1UL);

            // res.pab = (6a - 5) * (2a - 1)
            mpz_mul(res.pab, tmp, tmp2);

            // tmp2 = 6a - 1
            mpz_mul_ui(tmp2, a, 6UL);
            mpz_sub_ui(tmp2, tmp2, 1UL);

            // res.pab *= (6a - 1)
            mpz_mul(res.pab, res.pab, tmp2);

            // res.qab = a^3 * c3
            mpz_mul(res.qab, a, a);       // a^2
            mpz_mul(res.qab, res.qab, a); // a^3
            mpz_mul(res.qab, res.qab, c3);
        }
        // tmp2 = 545140134 * a + 13591409
        mpz_mul_ui(tmp2, a, 545140134UL);
        mpz_add_ui(tmp2, tmp2, 13591409UL);

        // tmp = res.pab * (13591409 + 545140134 * a)
        mpz_mul(tmp, res.pab, tmp2);

        if (mpz_odd_p(a)) {
            // neg is a is odd
            mpz_neg(res.tab, tmp);
        } else {
            mpz_set(res.tab, tmp);
        }
    } else {
        mpz_add(tmp, a, b);
        mpz_set_ui(tmp2, 2);
        mpz_div(diff, tmp, tmp2);
        resLow = bs(a, diff, c3);
        resHigh = bs(diff, b, c3);
        mpz_mul(res.pab, resLow.pab, resHigh.pab);
        mpz_mul(res.qab, resLow.qab, resHigh.qab);
        mpz_mul(tmp, resLow.tab, resHigh.qab);
        mpz_mul(tmp2, resHigh.tab, resLow.pab);
        mpz_add(res.tab, tmp, tmp2);
    }
    return res;
}

void chudBSPi(double digits, mpz_t res) {
    mpz_t c, c3, tmp;
    result binsplit;
    mpz_init(binsplit.pab);
    mpz_init(binsplit.qab);
    mpz_init(binsplit.tab);
    mpz_init(res);
    mpz_init(tmp);
    mpz_init(c);
    mpz_init(c3);

    mpz_set_ui(c, 640320UL);
    mpz_mul(c3, c, c);
    mpz_mul(c3, c3, c);
    mpz_div_ui(c3, c3, 24UL);

    mpz_div_ui(tmp, c3, 24UL);
    double digitsPerTerm = mpz_get_d(tmp);
    double n = floor(digits / digitsPerTerm) + 1.0;
    mpz_set_d(tmp, n);
    mpz_set_ui(c, 0UL);
    binsplit = bs(c, tmp, c3);

    unsigned long exp = (unsigned long)(2 * digits);
    mpz_ui_pow_ui(tmp, 10UL, exp);   // tmp = 10^(2*digits)

    mpz_mul_ui(tmp, tmp, 10005UL);
    mpz_sqrt(tmp, tmp);

    mpz_mul_ui(tmp, tmp, 426880UL);
    mpz_mul(tmp, tmp, binsplit.qab);
    mpz_div(res, tmp, binsplit.tab);
}

int main(void) {
    mpz_t pi;
    char *piOut;
    clock_t start_time = clock();
    chudBSPi(100000, pi);
    double elapsed = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    piOut = mpz_get_str(NULL, 10, pi);
    printf("%s\n100,000 digits in %fs\n", piOut, elapsed);
    return 0;
}