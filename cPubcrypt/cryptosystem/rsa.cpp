#include <../includes/cryptosystem.hpp>

struct RSA_PUBLIC_KEY {
	int key_size;
	mpz_t public_exponent;
	mpz_t public_modulus;
};

struct RSA_PRIVATE_KEY {
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
		RSA_KEYPAIR()
		void check_validity();

		void encrypt();
		void decrypt();
		void sign();
		void check_sign();

		//attributes
        RSA_PUBLIC_KEY rsa_pub_key;
        RSA_PRIVATE_KEY rsa_pv_key;

    private:
		//methods
		void generate(int bitSize, int public_exponent);
};


RSA_KEYPAIR::RSA_KEYPAIR();
void RSA_KEYPAIR::check_validity();

void RSA_KEYPAIR::generate();
void RSA_KEYPAIR::encrypt();
void RSA_KEYPAIR::decrypt();
void RSA_KEYPAIR::sign();
void RSA_KEYPAIR::check_sign();