/*

Code is borrowed from HOEVEN, LARRIEU, and LECERF.

*/

#ifndef _TRANSPOSE_BIT_H_
#define _TRANSPOSE_BIT_H_

#include <stdint.h>
#include <immintrin.h>
#include "bitpolymul2/defines.h"


static uint64_t _tr_bit_mask_4[4] BIT_POLY_ALIGN(32) = {0x00000000f0f0f0f0ULL,0x00000000f0f0f0f0ULL,0x00000000f0f0f0f0ULL,0x00000000f0f0f0f0ULL};
static uint64_t _tr_bit_mask_2[4] BIT_POLY_ALIGN(32) = {0x0000cccc0000ccccULL,0x0000cccc0000ccccULL,0x0000cccc0000ccccULL,0x0000cccc0000ccccULL};
static uint64_t _tr_bit_mask_1[4] BIT_POLY_ALIGN(32) = {0x00aa00aa00aa00aaULL,0x00aa00aa00aa00aaULL,0x00aa00aa00aa00aaULL,0x00aa00aa00aa00aaULL};


static inline
__m256i tr_bit_8x8_b4_ymmx1( __m256i n ) {
	__m256i a;

	a = and256(xor256(_mm256_srli_epi64(n,28),n),(*(__m256i*)_tr_bit_mask_4));  n=xor256(n, a);
	a = _mm256_slli_epi64(a,28); n = xor256(n, a);
	a = and256(xor256(_mm256_srli_epi64(n,14),n),(*(__m256i*)_tr_bit_mask_2));  n = xor256(n, a);
	a = _mm256_slli_epi64(a,14);  n = xor256(n, a);
	a = and256(xor256(_mm256_srli_epi64(n,7),n),(*(__m256i*)_tr_bit_mask_1));  n = xor256(n, a);
	a = _mm256_slli_epi64(a,7);  n = xor256(n, a);

	return n;
}


static inline
void tr_bit_8x8_b4_avx( uint8_t * _r , const uint8_t * m ) {

	__m256i n = _mm256_load_si256( (__m256i*) m );
	__m256i r = tr_bit_8x8_b4_ymmx1( n );
	_mm256_store_si256( (__m256i*) _r , r );
}



#endif


