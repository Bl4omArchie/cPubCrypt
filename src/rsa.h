#ifndef RSA_H
#define RSA_H

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

// prime.c
int get_prime_factors(mpz_t *prime_p, mpz_t *prime_q, int e, int prime_size);

// rsa.c
int generate(int key_size);

//random.c
void generate_random_odd(mpz_t rand_num, int size);
int is_probably_prime(mpz_t n, int iterations);

#endif