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
  int ite,j;
  poly a, u, v, s, t;
  
  //randombytes(msg0,  128);
  //randombytes(coins, 128);
 for(int i=0;i<128; i++)
    {
        msg0[i]=i;
    }
    for(int i=0;i<128; i++)
    {
        coins[i]=i;
    }
  
    printf("\n");
    printf("\n");

  for(ite=0; ite<1; ite++)
  {
    //Alice generates a public key

    wookie_pke_keypair(pk, sk);
    //Bob encrypts msg0 to Alice's public key

    for(j=0;j<WOOKIE_PKE_BYTES;j++)
    {
  	printf("%d ", msg0[j]);
    }
    printf("\n");
    printf("\n");

    wookie_pke_encrypt(ct, msg0, pk, coins,&a);
    for(j=0;j<WOOKIE_PKE_CIPHERTEXTBYTES;j++)
    {
  	printf("%u ", ct[j]);
    }
    printf("\n");
    printf("\n");

    /*for(j=0;j<WOOKIE_PKE_BYTES;j++)
    {
  	printf("%u ", msg0[j]);
    }*/

    //printf("\n");
    //printf("\n");
    //Alice decrypts to obtain msg1

    wookie_pke_decrypt(ct, sk, &u, &v, &s ,&t);
    printf("\nU\n");
    for(int j=0;j<WOOKIE_N;j++)
    {
  	printf("%u ", u.coeffs[j]);
    }
  printf("\nV\n");
    for(int j=0;j<WOOKIE_N;j++)
    {
  	printf("%u ", v.coeffs[j]);
    }

  printf("\n\nS\n");
    for(int j=0;j<WOOKIE_N;j++)
    {
  	printf("%u ", s.coeffs[j]);
    }

  printf("\nt\n");
    for(int j=0;j<WOOKIE_N;j++)
    {
  	printf("%u ", t.coeffs[j]);
    }

  printf("\nt\n");
    for(int j=0;j<WOOKIE_N;j++)
    {
  	printf("%u ", t.coeffs[j]);
    }
    printf("\nmsg1\n");
    for(j=0;j<WOOKIE_PKE_BYTES;j++)
    {
  	printf("%u ", msg1[j]);
    }
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
  poly a;

  int ite;

   randombytes(msg0,  WOOKIE_PKE_BYTES);
   randombytes(coins, WOOKIE_PKE_BYTES);

  printf("%d", CRYPTO_BYTES);

  for(i=0; i<1; i++)
  {
    //Alice generates a public key
    wookie_pke_keypair(pk, sk);

    //Bob encrypts msg0 to Alice's public key
    wookie_pke_encrypt(ct, msg0, pk, coins, &a);
  
    //Replace secret key with random values
    randombytes(sk, WOOKIE_PKE_SECRETKEYBYTES);

    //Alice decrypts to obtain msg1
    //wookie_pke_decrypt(msg1, ct, sk, &u, &v, &s ,&t);
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
  //ret |= test_invalid_sk();

  if(!ret) printf("True\n");
  
  return 0;
}
