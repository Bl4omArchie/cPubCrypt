# cPubCrypt

cPubCrypt is the C version of PubCrypt. The idea stay the same but with a new specifity: Bignum. To handle big numbers, I'm using GMP library 


## Compilation
```
gcc main.c src/*.c src/*.h -o rsa.o -lgmp
```

## Sources:
- [GMP man](https://gmplib.org/manual/)
- [NIST FIPS 186-4](https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.186-4.pdf)