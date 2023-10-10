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
        generate_random(kp_struct->p_factor, prime_size);                           //step 4.2 
        mpz_setbit(kp_struct->p_factor, 0);                                         //step 4.3
        mpz_sub_ui(kp_struct->p_factor_minus_one, kp_struct->p_factor, 1);          //storing p-1 in RSA_KEYPAIR

        // steps 4.4 - Check if p < sqrt(2)^(2(nlen/2 - 1))
        mpz_mul(tmp, tmp_square_root, tmp_prime_size);
        if (mpz_cmp(kp_struct->p_factor, tmp) >= 0) {
            gcd(tmp, kp_struct->p_factor_minus_one, kp_struct->public_exponent);    //step 4.5

            if (mpz_cmp_ui(tmp, 1) == 1) {
                if (is_probably_prime(kp_struct->p_factor, prime_size) == 1){                   //steps 4.5.1 & 4.5.2
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
        generate_random(kp_struct->q_factor, prime_size);                       //step 5.2
        mpz_setbit(kp_struct->q_factor, 0);                                     //step 5.3

        mpz_sub_ui(kp_struct->q_factor_minus_one, kp_struct->q_factor, 1);          //storing q-1 in RSA_KEYPAIR
        mpz_sub(kp_struct->p_minus_q, kp_struct->p_factor, kp_struct->q_factor);    //storing |p-q| in RSA_KEYPAIR
        mpz_abs(kp_struct->p_minus_q, kp_struct->p_minus_q);

        mpz_mul(tmp, tmp_square_root, tmp_prime_size2);
        if (mpz_cmp(kp_struct->p_minus_q, tmp) > 0) {
            mpz_mul(tmp, tmp_square_root, tmp_prime_size);

            if (mpz_cmp(kp_struct->q_factor, tmp) >= 0) {
                if (is_probably_prime(kp_struct->q_factor, prime_size) == 1){                   
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
        mpz_clear(tmp_prime_size2); 
        mpz_clear(tmp_square_root);
        return output;
}


/*Python implementation:
def miller_rabin(p, r):
    s, d = 0, p - 1
    while d & 1 == 0:
        d >>= 1
        s += 1

    for _ in range(r):
        a = randrange(2, p - 2)
        x = pow(a, d, p)
        if x == 1 or x == p - 1:
            continue
        for _ in range(s - 1):
            x = pow(x, 2, p)
            if x == p - 1:
                break
        else:
            return 0

    return 1
*/

int is_probably_prime(mpz_t candidate, int wLen) {
    // Miller-Rabin
    mpz_t d, s, z, cmo;
    mpz_init(d);
    mpz_init(s);
    mpz_init(z);
    mpz_init(cmo);

    int output = 0;
    int a=0;

    //step 1
    mpz_sub_ui(cmo, candidate, 1);
    mpz_set(d, cmo);
    while (mpz_even_p(d)) {
        mpz_div_ui(d, d, 2); // d >>= 1
        a++;
    }

    //step 4
    for (int i=0; i<MILLER_RABIN_ROUND; i++) {
        generate_random(s, wLen);               //4.2
        pow_fast(z, s, d, candidate);           //4.3

        if (mpz_cmp_ui(z, 1) > 0 && mpz_cmp(z, cmo) < 0) {      //4.4
            for (int j=1; j<a-1; j++) {                         //4.5
                mpz_powm_ui(z, z, 2, candidate);
                if (mpz_cmp(z, cmo) == 0) 
                    continue;
                if (mpz_cmp_ui(z, 1) == 0)
                    goto end_func;
            }
        }                                 
    }
    output = 1;
    goto end_func;                              
    
    end_func:
        mpz_clear(d);
        mpz_clear(s);
        mpz_clear(z);
        mpz_clear(cmo);
        return output;
}