#include "rsa.h"


/*
Goal: https://members.loria.fr/PZimmermann/papers/recbinary.pdf

Old python implementation:

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

void gcd(mpz_t *result, mpz_t a, mpz_t b) {

}