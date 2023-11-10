# cPubCrypt

cPubcrypt is the C/C++ version of my previous project Pubcrypt. I challenged myself with this new project because I wanted to add more features and handle more programming notions.
This library intends to implement the RSA cryptosystem and give the main primitives such as keypair generation, encryption, decryption and more. 

Whats new ?
- Bignum: using GMP library I'm managing myself big numbers 
- OOP: I've decided to write this library mainly in C++ so I could easily use OOP and offer a cleanest implementation of RSA 
- Revision of arithmethics algorithm: with my benchmark in Pubcrypt I already tryied to implement the fastet algorithm possible. This time I'm going further with more efficient implementation (inspiration: CADO NFS).

## Code organization

In this section I'm detailling my code organization: class, struct and everything you need to know about cPubcrypt library !

### Class

```cpp
class RSA_KEYPAIR 
{
    public:
		//methods
		RSA_KEYPAIR(Struct_pub_key pub_key, Struct_pv_key pv_key);
		void check_validity();

		void encrypt();
		void decrypt();
		void sign();
		void check_sign();

		//attributes
        Struct_pub_key rsa_pub_key;
        Struct_pv_key rsa_pv_key;

    private:
		//methods
		void generate(int bitSize);
};
```


### Structures
```cpp
struct Struct_pub_key {
	int key_size;
	mpz_t public_exponent;
	mpz_t public_modulus;
};

```
```cpp
struct Struct_pv_key {
	mpz_t private_exponent;
	mpz_t public_modulus;
	mpz_t prime_factor_p;
	mpz_t prime_factor_q;
	mpz_t dP;
	mpz_t dQ;
	mpz_t qInv;  
};
```

### Modules

None, everything is self made !




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