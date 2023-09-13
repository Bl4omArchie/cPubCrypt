#ifndef RSA_H
#define RSA_H

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// prime.c
int get_prime_factors(mpz_t *prime_p, mpz_t *prime_q, int prime_size);

// rsa.c
int generate(int key_size);


// arithmetic.c
void gcd(mpz_t *result, mpz_t a, mpz_t b);


#endif