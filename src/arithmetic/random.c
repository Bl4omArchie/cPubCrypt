#include "util.h"
#include <fcntl.h>
#include <unistd.h>


/*
readSecureRandomSeed(): generate a seed using /dev/urandom 
generate_random_odd(): generate an odd random number
*/


unsigned long int readSecureRandomSeed() {
    int urandom_fd = open("/dev/urandom", O_RDONLY);
    
    if (urandom_fd == -1) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    
    unsigned long int seed;
    ssize_t result = read(urandom_fd, &seed, sizeof(seed));
    
    if (result == -1) {
        perror("Failed to read from /dev/urandom");
        close(urandom_fd);
        exit(EXIT_FAILURE);
    }
    
    close(urandom_fd);
    return seed;
}

void generate_random(mpz_t rand_num, int size) {
    gmp_randstate_t state;

    gmp_randinit_default(state);
    gmp_randseed_ui(state, readSecureRandomSeed());

    mpz_urandomb(rand_num, state, size);
    gmp_randclear(state);
}