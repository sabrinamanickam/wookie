#ifndef PARAMS_H
#define PARAMS_H

#define WOOKIE_N      1024
#define WOOKIE_LOGQ     16
#define WOOKIE_Q      (1<<WOOKIE_LOGQ)
#define WOOKIE_K         8
#define WOOKIE_SYMBYTES 32

#define WOOKIE_PKE_SECRETKEYBYTES WOOKIE_POLYBYTES
#define WOOKIE_PKE_PUBLICKEYBYTES (WOOKIE_POLYBYTES+WOOKIE_SYMBYTES)
#define WOOKIE_PKE_CIPHERTEXTBYTES (2*WOOKIE_POLYBYTES)
#define WOOKIE_PKE_BYTES (WOOKIE_N/8)

#define WOOKIE_POLYBYTES  ((WOOKIE_N*WOOKIE_LOGQ)/8)

#endif

