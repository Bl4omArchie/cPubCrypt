# cPubCrypt

cPubCrypt is the C version of PubCrypt. The idea stay the same but with a new specifity: Bignum. To handle big numbers, I'm using GMP library 

## Installation and compilation
```
git clone https://github.com/Bl4omArchie/cPubCrypt
cd cPubcrypt
make
./rsa 2048
```


## RSA_KEYPAIR structure

```py
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
``` 
This structure store every required informations for generating a RSA keypair. I still don't know how I'm going to manage the data at the end of the program but I have several possible scenarios:
- call my library from your code and get the key directly from the struct
- execute the binary and retrieve the key in a PEM file
- the program print the public (n, e) and the private key (n, d) in the console

Note: I'm storing p-1 and q-1 it is for computing the phi number and the CRT (Chinese Remainder Theorem).

## RNG function

The RNG is coded in the src/arithmetic/random.c file:
```c
void generate_random_odd(mpz_t rand_num, int size);
unsigned long int readSecureRandomSeed();
```

The funcion generate_random_odd generate an odd number for the get_prime_factors algorithm. 
The seed is taken from the /dev/urandom file.

## References:

- [Digital Signature Standard (DSS) - FIPS 186-4](https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.186-4.pdf)
- [Recommendation for Pair-Wise Key Establishment Using Integer Factorization Cryptography](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-56Br2.pdf)
- [PKCS #1 Version 2.2: RSA Cryptography Specifications draft-moriarty-pkcs1-01](https://datatracker.ietf.org/doc/pdf/draft-moriarty-pkcs1-01.pdf)
- [Finding Large Primes for Public Key Cryptography - Glenn Henshaw](https://ghenshaw-work.medium.com/finding-large-primes-for-public-key-cryptography-9c5a5c0d32c4)
- [Mathematics of Public Key Cryptography - Steven D Galbraith](https://www.math.auckland.ac.nz/~sgal018/crypto-book/main.pdf)
- An Introduction to Mathematical Cryptography - Jeffrey Hoffstein, Jill Pipher, Joseph H. Silverman
- FAST GENERATION OF RANDOM, STRONG RSA PRIMES - Robert D. Silverman - RSA Laboratories - May 17, 1997
- Cryptosystème RSA - Anca Nitulescu - Ecole Normale Supérieure, Paris
- [A Warm Welcome to ASN.1 and DER - Let's Encrypt](https://letsencrypt.org/fr/docs/a-warm-welcome-to-asn1-and-der/)
- [GMP documentation](https://gmplib.org/manual/)
- [Speeding up the Division and Square Root of Power Series - Guillaume Hanrot, Michel Quercia, Paul Zimmermann](https://inria.hal.science/inria-00072675v1/document)
- [Algorithms for Modern Hardware - Sergey Slotin](https://en.algorithmica.org/hpc/)
- [Parallel integer multiplication - VIVIEN Samuel](https://hal.science/hal-03541726/document)