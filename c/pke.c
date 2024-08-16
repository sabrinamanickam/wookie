#include <string.h>
#include <stdio.h>
#include "params.h"
#include "poly.h"
#include "shake256.h"
#include "randombytes.h"

extern int jazz_wookie_pke_keypair(uint8_t pk[WOOKIE_PKE_PUBLICKEYBYTES],uint8_t sk[WOOKIE_PKE_SECRETKEYBYTES]);
int wookie_pke_keypair(unsigned char *pk, unsigned char *sk)
{
  jazz_wookie_pke_keypair(pk,sk);
  return 0;
}

extern int jazz_wookie_pke_encrypt(uint8_t ct[WOOKIE_PKE_CIPHERTEXTBYTES],uint8_t msg[WOOKIE_PKE_BYTES],uint8_t pk[WOOKIE_PKE_PUBLICKEYBYTES],uint8_t coins[WOOKIE_SYMBYTES]);
int wookie_pke_encrypt(unsigned char *ct, const unsigned char*msg, const unsigned char *pk, const unsigned char *coins)
{
 
  jazz_wookie_pke_encrypt(ct,msg,pk,coins);
  return 0;
}

extern int jazz_wookie_pke_decrypt(uint8_t msg[WOOKIE_PKE_BYTES],uint8_t ct[WOOKIE_PKE_CIPHERTEXTBYTES], uint8_t sk[WOOKIE_PKE_SECRETKEYBYTES]);
int wookie_pke_decrypt(unsigned char *msg,
                       const unsigned char *ct, 
                       const unsigned char *sk)
{

  jazz_wookie_pke_decrypt(msg,ct,sk);

  return 0;
}

