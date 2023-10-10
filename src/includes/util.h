#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>
#include "rsa.h"


//gcd.c
void gcd(mpz_t result, mpz_t x, mpz_t y);

//exp.c
void pow_fast(mpz_t result, mpz_t b, mpz_t e, mpz_t m);

//random.c
void generate_random(mpz_t rand_num, int size);
unsigned long int readSecureRandomSeed();

// prime.c
int get_prime_factors(struct RSA_KEYPAIR *kp_struct);
int is_probably_prime(mpz_t candidate, int wLen);

#endif