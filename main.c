#include <stdio.h>
#include <stdlib.h>
#include "src/includes/rsa.h"


int main(int argc, char *argv[]) {
	//start generation. You'll get all the needed data from the RSA_KEYPAIR structure
	if (generate(atoi(argv[1]))) {
		printf ("KeyPair generated with success ! You can access the key from the RSA_KEYPAIR struct\n");
		return EXIT_SUCCESS;
	}
	    
	else {
		printf ("An error occur, please retry");
		return EXIT_FAILURE;
	}
}