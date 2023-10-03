#ifndef RSA_H
#define RSA_H

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>



// rsa.c
int generate(int key_size);


//This structure contain all the necessary information for computing an RSA keypair. 
//Yet the program return the public/private key and clear this structure  
struct RSA_KEYPAIR {
    int key_size;
    mpz_t public_modulus;         //public modulus: n
    mpz_t public_exponent;        //public exponent: e
    mpz_t p_factor;               //prime factor: p
    mpz_t q_factor;               //prime factor: q
    mpz_t p_factor_minus_one;     //p-1
    mpz_t q_factor_minus_one;     //q-1
    mpz_t p_minus_q;              //|p-q|
    mpz_t private_exponent;       //private exponent: d
};

#endif