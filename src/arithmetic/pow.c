#include "util.h"

void pow_fast(mpz_t result, const mpz_t x, const mpz_t e, const mpz_t m) {
    mpz_set_ui(result, 1); // Initialize result to 1

    while (mpz_cmp_ui(e, 0) > 0) {
        if (mpz_tstbit(e, 0)) {
            mpz_mul(result, result, x); // result *= x
            if (m != NULL) {
                mpz_mod(result, result, m); // result %= m
            }
        }
        mpz_mul(x, x, x); // x *= x
        if (m != NULL) {
            mpz_mod(x, x, m); // x %= m
        }
        mpz_div_ui(e, e, 2); // e >>= 1
    }

    if (m != NULL) {
        mpz_mod(result, result, m); // result %= m
    }
}