#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

//gcd.c
void gcd(mpz_t result, mpz_t x, mpz_t y);

//pow.c
void pow_fast(mpz_t result, const mpz_t x, const mpz_t e, const mpz_t m);


//random.c
void generate_random_odd(mpz_t rand_num, int size);
int is_probably_prime(mpz_t n, int iterations);

// prime.c
int get_prime_factors(mpz_t *prime_p, mpz_t *prime_q, mpz_t e, int prime_size);
int is_probably_prime(mpz_t n, int iterations);

#endif