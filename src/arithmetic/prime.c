#include "util.h"   

#define SUCCESS 1
#define FAILURE 0
#define MILLER_RABIN_ROUND 5


/*
get_prime_factors() implements the appendix B.3.3 from NIST.FIPS.186-4

- Sensitive data are stored and read from the RSA_KEYPAIR tsruct
- Temporary computing are made in the tmp variable.

*/


int get_prime_factors(struct RSA_KEYPAIR *kp_struct) {
    mpz_t tmp;
    mpz_t sqrt_two;
    mpz_init(tmp);
    mpz_init(sqrt_two);

    int prime_size = kp_struct->key_size/2;
    mpz_set_str(sqrt_two, "2", 10);
    mpz_sqrt(sqrt_two, sqrt_two);
    int i = 0;

    // Generate p, steps 4
    while (i < 5 * kp_struct->key_size) {
        //steps 4.2 & 4.3
        generate_random_odd(kp_struct->p_factor, prime_size);
        //storing p-1 in RSA_KEYPAIR
        mpz_sub_ui(kp_struct->p_factor_minus_one, kp_struct->p_factor, 1);

        // steps 4.4 - Check if p < sqrt(2)^(2(nlen/2 - 1))
        mpz_mul_2exp(tmp, 2, prime_size - 1);
        mpz_mul(tmp, sqrt_two, tmp);
        if (mpz_cmp(kp_struct->p_factor, tmp) >= 0) {

            //steps 4.5
            gcd(tmp, kp_struct->p_factor_minus_one, kp_struct->public_exponent);
            if (mpz_cmp_ui(tmp, 1) == 1) {
                //steps 4.5.1 & 4.5.2
                if (is_probably_prime(kp_struct->p_factor) == 1){
                    mpz_clear(tmp);
                    break;
                }
            }
        }
        i++;
    }
    if (i >= 5 * prime_size) {
        printf("FAILURE: Unable to generate p.\n");
        return FAILURE;
    }

    // Generate q
    i = 0;
    while (i < 5 * kp_struct->key_size) {
        //steps 5.2 & 5.3
        generate_random_odd(kp_struct->q_factor, prime_size);
        //storing q-1 in RSA_KEYPAIR
        mpz_sub_ui(kp_struct->q_factor_minus_one, kp_struct->q_factor, 1);
        //storing |p-q| in RSA_KEYPAIR
        mpz_sub(kp_struct->p_minus_q, kp_struct->p_factor, kp_struct->q_factor);
        mpz_abs(kp_struct->p_minus_q, kp_struct->p_minus_q);


        
        i++;
    }       

    mpz_clear(tmp);
    printf("FAILURE: Unable to generate q.\n");
    return FAILURE;
}

int is_probably_prime(mpz_t n) {
    // Miller-Rabin
    return mpz_probab_prime_p(n, MILLER_RABIN_ROUND);
}