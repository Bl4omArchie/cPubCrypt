#include "util.h"

void generate_random_odd(mpz_t rand_num, int size) {
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));  // Seed with current time

    mpz_urandomb(rand_num, state, size);
    mpz_setbit(rand_num, 0);
    
    gmp_randclear(state);
}