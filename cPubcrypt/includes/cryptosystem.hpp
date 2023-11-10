#ifndef CRYPTOSYSTEM_HPP
#define CRYPTOSYSTEM_HPP

#include <stdexcept>
#include <iostream>
#include <gmp.h>


struct Struct_pub_key {
	int key_size;
	mpz_t public_exponent;
	mpz_t public_modulus;
};

struct Struct_pv_key {
	mpz_t private_exponent;
	mpz_t public_modulus;
	mpz_t prime_factor_p;
	mpz_t prime_factor_q;
	mpz_t dP;
	mpz_t dQ;
	mpz_t qInv;  
};


class RSA_KEYPAIR 
{
    public:
		//methods
        RSA_KEYPAIR() = default;
		RSA_KEYPAIR(Struct_pub_key pub_key, Struct_pv_key pv_key);
		void check_validity();

		void encrypt();
		void decrypt();
		void sign();
		void check_sign();

		//attributes
        Struct_pub_key rsa_pub_key;
        Struct_pv_key rsa_pv_key;
};

RSA_KEYPAIR generate(int bitSize);


#endif