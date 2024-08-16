#ifndef POLY_H
#define POLY_H

#endif
#include <string.h>
#include <stdio.h>
#include "params.h"
#include "poly.h"
#include "shake256.h"
#include "randombytes.h"

/* Element of Rq = Z_q[X]/(X^n+1) */
/* coeffs[0] + X*coeffs[1] + X^2*xoeffs[2] + ... + X^(n-1)*xcoeffs[n-1] */
typedef struct{
  uint16_t coeffs[WOOKIE_N];
} poly;

int wookie_pke_keypair(unsigned char *pk, 
                       unsigned char *sk);


int wookie_pke_encrypt(unsigned char *ct, 
                       const unsigned char *msg, 
                       const unsigned char *pk, 
                       const unsigned char *coins
                      );


int wookie_pke_decrypt(uint8_t msg[WOOKIE_PKE_BYTES],
                       const unsigned char *ct, 
                       const unsigned char *sk);