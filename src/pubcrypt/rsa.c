#include "rsa.h"
#include "util.h"


int generate(int key_size) {
    if (key_size < 2048 && key_size > 8192) {
        printf ("Wrong key size. It must be included in the range [2048; 8192]");
        return 0;
    }

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