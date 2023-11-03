
/* Python implementation from pubcrypt

def gcd(x, y):
    if x == 0:
        return y
    if y == 0:
        return x

    x_rightmost = x & -x
    y_rightmost = y & -y

    while x_rightmost != y_rightmost:
        if x_rightmost > y_rightmost:
            x_rightmost >>= 1
        else:
            y_rightmost >>= 1

    return x_rightmost

*/

void gcd(mpz_t result, mpz_t x, mpz_t y) {
    if (mpz_sgn(x) == 0) {
        mpz_set(result, y);
        return;
    }
    if (mpz_sgn(y) == 0) {
        mpz_set(result, x);
        return;
    }

    mpz_t x_rightmost, y_rightmost;
    mpz_init(x_rightmost);
    mpz_init(y_rightmost);

    mpz_set(x_rightmost, x);
    mpz_set(y_rightmost, y);

    while (mpz_cmp(x_rightmost, y_rightmost) != 0) {
        if (mpz_cmp(x_rightmost, y_rightmost) > 0) {
            mpz_tdiv_q_2exp(x_rightmost, x_rightmost, 1);
        } else {
            mpz_tdiv_q_2exp(y_rightmost, y_rightmost, 1);
        }
    }

    mpz_set(result, x_rightmost);

    mpz_clear(x_rightmost);
    mpz_clear(y_rightmost);
}