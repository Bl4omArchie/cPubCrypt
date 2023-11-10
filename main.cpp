#include <stdio.h>
#include <stdlib.h>

#include "cPubcrypt/includes/cryptosystem.hpp"


int main() {

    /*Two ways for using RSA_KEYPAIR class*/
    
    //1- construct the key
    Struct_pub_key pub_key {.key_size=2048, .public_exponent=65537, .public_modulus=187};
    Struct_pv_key pv_key {};

    RSA_KEYPAIR my_keypair = RSA_KEYPAIR(pub_key, pv_key);


    //2- generate the key
    RSA_KEYPAIR my_second_keypair;
    my_second_keypair = generate(2048);

    return 1;
}