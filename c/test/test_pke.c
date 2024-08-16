#include <stdio.h>
#include <string.h>
#include "../api.h"
#include "../params.h"
#include "../randombytes.h"
#include "../pke.h"
#include "../pke.c"

#define NTESTS 10

int test_encdec(void)
{
  unsigned char pk[WOOKIE_PKE_PUBLICKEYBYTES];
  unsigned char sk[WOOKIE_PKE_SECRETKEYBYTES];
  unsigned char ct[WOOKIE_PKE_CIPHERTEXTBYTES];
  unsigned char msg0[WOOKIE_PKE_BYTES];
  unsigned char msg1[WOOKIE_PKE_BYTES];
  unsigned char coins[WOOKIE_SYMBYTES];
  unsigned long i;

  randombytes(msg0,  WOOKIE_PKE_BYTES);
 /* for(int j=0;j<128;j++)
    {
      printf("%u " ,msg0[j]);
    }*/
    printf("\n");
  randombytes(coins, WOOKIE_PKE_BYTES);

  for(i=0; i<1; i++)
  {
    //Alice generates a public key
    wookie_pke_keypair(pk, sk);
    
    //Bob encrypts msg0 to Alice's public key
    wookie_pke_encrypt(ct, msg0, pk, coins);
    
    //Alice decrypts to obtain msg1
    wookie_pke_decrypt(msg1,ct, sk);
    /*for(int j=0;j<128;j++)
    {
      printf("%u " ,msg1[j]);
    }*/
    if(memcmp(msg0, msg1, WOOKIE_PKE_BYTES))
    {
      printf("ERROR1: decrypted message does not match encrypted message\n");
      return -1;
    }
  }

  return 0;
}


int test_invalid_sk(void)
{
  unsigned char pk[WOOKIE_PKE_PUBLICKEYBYTES];
  unsigned char sk[WOOKIE_PKE_SECRETKEYBYTES];
  unsigned char ct[WOOKIE_PKE_CIPHERTEXTBYTES];
  unsigned char msg0[WOOKIE_PKE_BYTES];
  unsigned char msg1[WOOKIE_PKE_BYTES];
  unsigned char coins[WOOKIE_SYMBYTES];
  unsigned long i;

  int ite;

   randombytes(msg0,  WOOKIE_PKE_BYTES);
   randombytes(coins, WOOKIE_PKE_BYTES);


  for(i=0; i<1; i++)
  {
    //Alice generates a public key
    wookie_pke_keypair(pk, sk);

    //Bob encrypts msg0 to Alice's public key
    wookie_pke_encrypt(ct, msg0, pk, coins);
  
    //Replace secret key with random values
    randombytes(sk, WOOKIE_PKE_SECRETKEYBYTES);

    //Alice decrypts to obtain msg1
    wookie_pke_decrypt(msg1,ct, sk);
    if(!memcmp(msg0, msg1, WOOKIE_PKE_BYTES))
    {
      printf("ERROR2: decryption with invalid secret key succeeds\n");
      return -1;
    }
  }

  return 0;
}


int main(void)
{
  int ret = 0;
  ret |= test_encdec();
  ret |= test_invalid_sk();

  if(!ret) printf("True\n");
  
  return 0;
}
