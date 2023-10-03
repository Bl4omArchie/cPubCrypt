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
    int prime_size = kp_struct->key_size/2;
    int output;

    //temporary values
    mpz_t tmp;
    mpz_t tmp_square_root;
    mpz_t tmp_prime_size;
    mpz_t tmp_prime_size2;
    mpz_init(tmp);
    mpz_init(tmp_square_root);
    mpz_init(tmp_prime_size);
    mpz_init(tmp_prime_size2);

    //square root of 2
    mpz_set_ui(tmp_square_root, 2);
    mpz_sqrt(tmp_square_root, tmp_square_root);

    //2^prime_size-1
    mpz_ui_pow_ui(tmp_prime_size, 2, prime_size - 1);
    //2^prime_size-100
    mpz_ui_pow_ui(tmp_prime_size2, 2, prime_size - 100);


    int i = 0;
    while (i < 5 * kp_struct->key_size) {                                           // Generate p, steps 4
        generate_random_odd(kp_struct->p_factor, prime_size);                       //steps 4.2 & 4.3
        mpz_sub_ui(kp_struct->p_factor_minus_one, kp_struct->p_factor, 1);          //storing p-1 in RSA_KEYPAIR

        // steps 4.4 - Check if p < sqrt(2)^(2(nlen/2 - 1))
        mpz_mul(tmp, tmp_square_root, tmp_prime_size);
        if (mpz_cmp(kp_struct->p_factor, tmp) >= 0) {
            gcd(tmp, kp_struct->p_factor_minus_one, kp_struct->public_exponent);    //step 4.5

            if (mpz_cmp_ui(tmp, 1) == 1) {
                if (is_probably_prime(kp_struct->p_factor) == 1){                   //steps 4.5.1 & 4.5.2
                    break;
                }
            }
        }
        i++;
    }
    if (i >= 5 * prime_size) {
        printf("FAILURE: Unable to generate p.\n");
        output = FAILURE;
        goto end_func;
    }


    // Generate q, step 5
    i = 0;
    while (i < 5 * kp_struct->key_size) {
        generate_random_odd(kp_struct->q_factor, prime_size);                       //steps 5.2 & 5.3
        
        mpz_sub_ui(kp_struct->q_factor_minus_one, kp_struct->q_factor, 1);          //storing q-1 in RSA_KEYPAIR
        mpz_sub(kp_struct->p_minus_q, kp_struct->p_factor, kp_struct->q_factor);    //storing |p-q| in RSA_KEYPAIR
        mpz_abs(kp_struct->p_minus_q, kp_struct->p_minus_q);

        mpz_mul(tmp, tmp_square_root, tmp_prime_size2);
        if (mpz_cmp(kp_struct->p_minus_q, tmp) > 0) {
            mpz_mul(tmp, tmp_square_root, tmp_prime_size);

            if (mpz_cmp(kp_struct->q_factor, tmp) >= 0) {
                if (is_probably_prime(kp_struct->q_factor) == 1){                   
                    output = SUCCESS;                                               //a valid p and q were found
                    goto end_func;
                }  
            }
        }
        i++;
    }      
    //if we exit this loop, it means we failed finding q 
    printf("FAILURE: Unable to generate q.\n");
    output = FAILURE;
    goto end_func;
    
    //proper way to end the function. Always exit with a goto end_func
    end_func:
        mpz_clear(tmp);
        mpz_clear(tmp_prime_size);
        mpz_clear(tmp_square_root);
        mpz_clear(tmp_prime_size2);
        return output;
}


int is_probably_prime(mpz_t n) {
    // Miller-Rabin
    return mpz_probab_prime_p(n, MILLER_RABIN_ROUND);
}