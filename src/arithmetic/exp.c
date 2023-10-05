#include "util.h"


/* Python implementation from pubcrypt
def pow_fast(b, e, m):
    result = 1
    while e > 0:
        if e & 1:
            result *= b
            if m:
                result %= m
        b *= b
        if m:
            b %= m
        e >>= 1

        if b == 0 and m:
            b = 1  
        if m == 0:
            m = 1 
    if m:
        result %= m
    return result
*/

void pow_fast(mpz_t *result, mpz_t b, mpz_t e, mpz_t m) {
    mpz_set_ui(result, 1);

    while (mpz_cmp_ui(e, 0) > 0) {
        if (mpz_tstbit(e, 0)) {
            mpz_mul(result, result, b);
            if (mpz_cmp_ui(m, 0) != 0) {
                mpz_mod(result, result, m);
            }
        }
        mpz_mul(b, b, b);
        if (mpz_cmp_ui(m, 0) != 0) {
            mpz_mod(b, b, m);
        }
        mpz_fdiv_q_2exp(e, e, 1);

        if (mpz_cmp_ui(b, 0) == 0 && mpz_cmp_ui(m, 0) != 0) {
            mpz_set_ui(b, 1);
        }
        if (mpz_cmp_ui(m, 0) == 0) {
            mpz_set_ui(m, 1);
        }
    }

    if (mpz_cmp_ui(m, 0) != 0) {
        mpz_mod(result, result, m);
    }
}