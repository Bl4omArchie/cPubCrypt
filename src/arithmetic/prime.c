#include "util.h"

#define SUCCESS 1
#define FAILURE 0


void generate_random_int(mpz_t result, int bit_length) {
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    mpz_rrandomb(result, state, bit_length);
    mpz_setbit(result, 0);                      // Ensure it's odd
    gmp_randclear(state);
}


int get_prime_factors(mpz_t *prime_p, mpz_t *prime_q, mpz_t e, int prime_length) {
    mpz_t candidate_p, candidate_q, gcd_result;
    mpz_init(candidate_p);
    mpz_init(candidate_q);
    mpz_init(gcd_result);

    int i = 0;

    // Generate p
    while (i < 5 * prime_length) {
        generate_random_int(candidate_p, prime_length / 2);

        if (mpz_cmp_ui(candidate_p, 1 << (prime_length- 1)) >= 0) {
            gcd(gcd_result, candidate_p-1, e);
            if (mpz_cmp_ui(gcd_result, 1) == 1) {
                if (is_probably_prime(candidate_p, 25)) {
                    break;
                }
            }
        }

        i++;
    }

    if (i >= 5 * prime_length) {
        printf("FAILURE: Unable to generate p.\n");
        return FAILURE;
    }

    i = 0;

    // Generate q
    while (i < 5 * prime_length) {
        generate_random_int(candidate_q, prime_length);

        if (mpz_cmp_ui(candidate_q, 1 << (prime_length - 1)) >= 0) {
            gcd(gcd_result, candidate_q-1, e);
            if (mpz_cmp_ui(gcd_result, 1) == 1) {
                if (is_probably_prime(candidate_q, 25)) {
                    if (mpz_cmpabs(candidate_p, candidate_q) > (1 << (prime_length - 100))) {
                        prime_p = &candidate_p;                                                     //storing the prime p into a pointer so it can be retrieve in the generate() function 
                        prime_q = &candidate_q;                                                     //same with the prime q

                        mpz_clear(candidate_p);
                        mpz_clear(candidate_q);
                        mpz_clear(gcd_result);
                        return SUCCESS;
                    }
                }
            }
        }
        i++;
    }       

    mpz_clear(candidate_p);
    mpz_clear(candidate_q);
    mpz_clear(gcd_result);
    printf("FAILURE: Unable to generate q.\n");
    return FAILURE;
}

int is_probably_prime(mpz_t n, int iterations) {
    // Miller-Rabin
    return mpz_probab_prime_p(n, iterations);
}