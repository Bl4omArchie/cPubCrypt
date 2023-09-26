#include "util.h"   

#define SUCCESS 1
#define FAILURE 0
#define MILLER_RABIN_ROUND 5


int get_prime_factors(struct RSA_KEYPAIR *kp_struct) {
    mpz_t gcd_result;
    mpz_init(gcd_result);

    int prime_size = kp_struct->key_size/2;
    int i = 0;

    // Generate p
    while (i < 5 * kp_struct->key_size) {
        generate_random_odd(kp_struct->p_factor, prime_size);
        mpz_sub_ui(kp_struct->p_factor_minus_one, kp_struct->p_factor, 1);

        if (mpz_cmp_ui(kp_struct->p_factor, 1 << (prime_size- 1)) >= 0) {
            gcd(gcd_result, kp_struct->p_factor_minus_one, kp_struct->public_exponent);

            if (mpz_cmp_ui(gcd_result, 1) == 1) {
                if (is_probably_prime(kp_struct->p_factor)) {
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
    while (i < 5 * prime_size) {
        generate_random_odd(kp_struct->q_factor, prime_size);
        mpz_sub_ui(kp_struct->q_factor_minus_one, kp_struct->q_factor, 1);

        if (mpz_cmp_ui(kp_struct->q_factor, 1 << (prime_size - 1)) >= 0) {
            gcd(gcd_result, kp_struct->q_factor_minus_one, kp_struct->public_exponent);

            if (mpz_cmp_ui(gcd_result, 1) == 1) {
                if (is_probably_prime(kp_struct->q_factor)) {
                    if (mpz_cmpabs(kp_struct->p_factor, kp_struct->q_factor) > (1 << (prime_size - 100))) {
                        mpz_clear(gcd_result);
                        return SUCCESS;
                    }
                }
            }
        }
        i++;
    }       

    mpz_clear(gcd_result);
    printf("FAILURE: Unable to generate q.\n");
    return FAILURE;
}

int is_probably_prime(mpz_t n) {
    // Miller-Rabin
    return mpz_probab_prime_p(n, MILLER_RABIN_ROUND);
}