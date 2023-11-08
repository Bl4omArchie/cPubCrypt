#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP


#include <iostream>
#include <gmp.h>



void gcd(mpz_t *result, mpz_t a, mpz_t b);
void pow_fast(mpz_t *result, mpz_t a, mpz_t b);

//prime.cpp
void get_prime_factors(mpz_t *prime_one, mpz_t *prime_two, int prime_size);

#endif