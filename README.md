# cPubCrypt

cPubCrypt is the C version of PubCrypt. The idea stay the same but with a new specifity: Bignum. To handle big numbers, I'm using GMP library 


## RSA_KEYPAIR structure

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


## Installation and compilation
```
git clone https://github.com/Bl4omArchie/cPubCrypt
cd cPubcrypt
make
./rsa 2048
```

## Sources:
- [GMP man](https://gmplib.org/manual/)
- [NIST FIPS 186-4](https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.186-4.pdf)
- FAST GENERATION OF RANDOM, STRONG RSA PRIMES - Robert D. Silverman - RSA Laboratories - May 17, 1997
- Cryptosystème RSA - Anca Nitulescu - Ecole Normale Supérieure, Paris