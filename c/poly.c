#include "params.h"
#include "poly.h"
#include "shake256.h"
#include "randombytes.h"

/*static uint16_t coeff_frombytes(const unsigned char *x)
{
  uint16_t r;
  r = x[1];
  r <<= 8;
  r += x[0];
  return r;
}
 
static void coeff_tobytes(unsigned char *r, uint16_t a)
{
  r[0] = a & 0xff;
  r[1] = a >> 8;
}

static unsigned char hamming(unsigned char a)
{
  int i;
  unsigned char r = 0;
  for(i=0;i<8;i++)
    r += ((a>>i) & 1);
  return r;
}*/

#if (WOOKIE_Q == 65536)
extern void jazz_poly_tobytes(unsigned char r[WOOKIE_POLYBYTES], const uint16_t a_coeffs[WOOKIE_N]);
void poly_tobytes(unsigned char r[WOOKIE_POLYBYTES], const poly *a)
{
 jazz_poly_tobytes(r,a->coeffs);
}
#else
#error "poly_tobytes only works for WOOKIE_Q == 65536"
#endif

#if (WOOKIE_Q == 65536)

extern void jazz_poly_frombytes(uint16_t r_coeffs[WOOKIE_N], const unsigned char b[WOOKIE_POLYBYTES]);
void poly_frombytes(poly *r, const unsigned char b[WOOKIE_POLYBYTES])
{
  jazz_poly_frombytes(r->coeffs,b);
}
#else
#error "poly_frombytes only works for WOOKIE_Q == 65536"
#endif

extern void jazz_poly_mul(uint16_t r_coeffs[WOOKIE_N],const uint16_t a_coeffs[WOOKIE_N],const uint16_t b_coeffs[WOOKIE_N]);

void poly_mul(poly *r, const poly *a, const poly *b)
{
 jazz_poly_mul(r->coeffs,a->coeffs,b->coeffs);
}

extern void jazz_ poly_add(uint16_t r_coeffs[WOOKIE_N],const uint16_t a_coeffs[WOOKIE_N],const uint16_t b_coeffs[WOOKIE_N]);

void poly_add(poly *r, const poly *a, const poly *b)
{
  jazz_poly_add(r->coeffs,a->coeffs,b->coeffs);
}
extern void jazz_poly_sub(uint16_t r_coeffs[WOOKIE_N],const uint16_t a_coeffs[WOOKIE_N],const uint16_t b_coeffs[WOOKIE_N]);

void poly_sub(poly *r, const poly *a, const poly *b)
{
  jazz_poly_sub(r->coeffs,a->coeffs,b->coeffs);
}

#if (WOOKIE_K == 8)
extern void jazz_poly_getnoise(uint16_t r_coeffs[WOOKIE_N], const unsigned char *seed0,unsigned char seed1 );
void poly_getnoise(poly *r, const unsigned char *seed0, unsigned char seed1)
{
  jazz_poly_getnoise(r->coeffs, seed0,seed1);
}
#else
#error "poly_getnoise only works for WOOKIE_K == 8"
#endif

extern void jade_xof_shake256_amd64_avx2(uint16_t r_coeffs[WOOKIE_N],int output_len, const unsigned char seed[WOOKIE_SYMBYTES], int input_len);
void poly_uniform(poly *r, const unsigned char seed[WOOKIE_SYMBYTES])
{
  int output_len=2048;
  int input_len=32;
  //XXX: make bigendian compatible
  //shake256((unsigned char *)r->coeffs,sizeof(r->coeffs),seed,WOOKIE_SYMBYTES);
  jade_xof_shake256_amd64_avx2(r->coeffs,output_len,seed,input_len);
}

extern void jazz_poly_frommsg(uint16_t r_coeffs[WOOKIE_N], const unsigned char m[WOOKIE_N/8]);

void poly_frommsg(poly *r, const unsigned char m[WOOKIE_N/8])
{
  jazz_poly_frommsg(r->coeffs, m);
}
extern void jazz_poly_tomsg(unsigned char m[WOOKIE_N/8], const uint16_t a_coeffs[WOOKIE_N]);
void poly_tomsg(unsigned char m[WOOKIE_N/8], const poly *a)
{
 jazz_poly_tomsg(m,a->coeffs);
}
 
