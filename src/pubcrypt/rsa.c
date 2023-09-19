#include "rsa.h"


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
    mpz_t private_exponent;       //private exponent: d
};  


int generate(int key_size) {
    /*
        1. Init mpz_t p, q
        2. generate p and q
        3. verify p and q with consistency test
        4. Give a structure of the RSA keypair
    */

    //As a simplification, public_exponent = 65537 
    struct RSA_KEYPAIR kp = {key_size, 65537 };

        
    //generation of prime factors p and q
    mpz_t *p = &kp.p_factor;
    mpz_t *q = &kp.q_factor;
    
    if (get_prime_factors(p, q, kp.public_exponent, key_size) == 1) {
        gmp_printf("p: %Zd\n", p);
        gmp_printf("q: %Zd\n", q);

        return 1;
    }

    else
        return 0;
}