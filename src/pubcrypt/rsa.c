#include "rsa.h"
#include "util.h"


int generate(int key_size) {
    /*
        1. Init mpz_t p, q
        2. generate p and q
        3. verify p and q with consistency test
        4. Give a structure of the RSA keypair
    */

    //I'm setting a pointer on the RSA_KEYPAIR struct 
    //As a simplification, public_exponent = 65537 
    struct RSA_KEYPAIR *kp_struct = &(struct RSA_KEYPAIR) {key_size, 65537};

    if (get_prime_factors(kp_struct) == 1) {
        gmp_printf("p: %Zd\n", kp_struct->p_factor);
        gmp_printf("q: %Zd\n", kp_struct->q_factor);

        return 1;
    }

    else
        return 0;
}