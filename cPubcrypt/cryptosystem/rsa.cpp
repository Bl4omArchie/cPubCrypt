#include <../includes/cryptosystem.hpp>
#include <../includes/algorithm.hpp>
#include "cryptosystem.hpp"



RSA_KEYPAIR::RSA_KEYPAIR(Struct_pub_key pub_key, Struct_pv_key pv_key) {
		this->rsa_pub_key = pub_key;
		this->rsa_pv_key = pv_key;
}


void RSA_KEYPAIR::check_validity() {

}
void RSA_KEYPAIR::encrypt(){
	
}
void RSA_KEYPAIR::decrypt(){
	
}
void RSA_KEYPAIR::sign(){
	
}
void RSA_KEYPAIR::check_sign(){
	
}


RSA_KEYPAIR generate(int bitSize){
	/*
	This implentation have a fixed public exponent (e = 65537)
	*/

	if (bitSize < 2048 || bitSize > 8192)
		throw ("Incorrect key size, the correct range is from 2048 bits to 8192 bits");
	
	struct Struct_pub_key 	  *ptr_struct_pub_key = &(struct Struct_pub_key) {.key_size=bitSize, .public_exponent=65537};
	struct Struct_pv_key 	  *ptr_struct_pv_key  = &(struct Struct_pv_key) {};

	get_prime_factors(&ptr_struct_pv_key->prime_factor_p, &ptr_struct_pv_key->prime_factor_q, (int)bitSize/2 );

    mpz_t tmp;
    mpz_t tmp_square_root;
    mpz_init(tmp);

	RSA_KEYPAIR result = RSA_KEYPAIR(*ptr_struct_pub_key, *ptr_struct_pv_key);
	//clean structures
	return result;
}