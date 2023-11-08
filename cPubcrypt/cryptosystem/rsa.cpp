#include <../includes/cryptosystem.hpp>
#include <../includes/algorithm.hpp>



RSA_KEYPAIR::RSA_KEYPAIR() {

}


void RSA_KEYPAIR::check_validity() {
	
}

void RSA_KEYPAIR::generate(int bitSize){
	/*
	This implentation have a fixed public exponent (e = 65537)
	*/

	if (bitSize < 2048 || bitSize > 8192)
		throw ("Incorrect key size, the correct range is from 2048 bits to 8192 bits");
	
	struct RSA_PUBLIC_KEY 	  *pub_key_struct = &(struct RSA_PUBLIC_KEY) {.key_size=bitSize, .public_exponent=65537};
	struct RSA_PRIVATE_KEY 	  *pv_key_struct  = &(struct RSA_PRIVATE_KEY) {};

	get_prime_factors(&pv_key_struct->prime_factor_p, &pv_key_struct->prime_factor_q, (int)bitSize/2 );

    mpz_t tmp;
    mpz_t tmp_square_root;
    mpz_init(tmp);
}



void RSA_KEYPAIR::encrypt(){
	
}
void RSA_KEYPAIR::decrypt(){
	
}
void RSA_KEYPAIR::sign(){
	
}
void RSA_KEYPAIR::check_sign(){
	
}