#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "hex.h"
#include <endian.h>
#include "sph_blake.h"
#include "sph_bmw.h"
#include "sph_groestl.h"
#include "sph_jh.h"
#include "sph_keccak.h"
#include "sph_skein.h"
#include "sph_luffa.h"
#include "sph_cubehash.h"
#include "sph_shavite.h"
#include "sph_simd.h"
#include "sph_echo.h"
#include "sph_hamsi.h"
#include "sph_fugue.h"
#include "sph_shabal.h"
#include "sph_whirlpool.h"
#include "sph_sha2.h"

#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define __USE_BSD

#ifdef _MSC_VER
# define _ALIGN(x) __declspec(align(x))
#else
# define _ALIGN(x) __attribute__ ((aligned(x)))
#endif

const char* HEX_ALGO_NAMES[HEX_HASH_FUNC_COUNT] = 
{
	"BLAKE",
	"BMW",
	"GROESTL",
	"JH",
	"KECCAK",
	"SKEIN",
	"LUFFA",
	"CUBEHASH",
	"SHAVITE",
	"SIMD",
	"ECHO",
	"HAMSI",
	"FUGUE",
	"SHABAL",
	"WHIRLPOOL",
	"SHA512"
};

static void be32enc_vect_hex(uint32_t *dst, const uint32_t *src, uint32_t len)
{
	uint32_t i;

	for (i = 0; i < len; i++)
	dst[i] = htobe32(src[i]);
}

void hex_hash(void *state, const void *input)
{
	unsigned char _ALIGN(64) hash[128];
	sph_blake512_context ctx_blake;
	sph_bmw512_context ctx_bmw;
	sph_groestl512_context ctx_groestl;
	sph_jh512_context ctx_jh;
	sph_keccak512_context ctx_keccak;
	sph_skein512_context ctx_skein;
	sph_luffa512_context ctx_luffa;
	sph_cubehash512_context ctx_cubehash;
	sph_shavite512_context ctx_shavite;
	sph_simd512_context ctx_simd;
	sph_echo512_context ctx_echo;
	sph_hamsi512_context ctx_hamsi;
	sph_fugue512_context ctx_fugue;
	sph_shabal512_context ctx_shabal;
	sph_whirlpool_context ctx_whirlpool;
	sph_sha512_context ctx_sha512;

	const void *in = input;
	int size = 80;
	uint8_t hashOrder[HEX_HASH_FUNC_COUNT];

	uint32_t *in32 = (uint32_t*) input;
	hex_getalgolist((uint8_t*)input + 4, hashOrder);

	uint8_t algo = hashOrder[0] % HEX_HASH_FUNC_COUNT; // initial algo
	for (int i = 0; i < HEX_HASH_FUNC_COUNT; i++)
	{
		//applog(LOG_WARNING, "%s", HEX_ALGO_NAMES[algo]);
		switch (algo) 
		{
			case HEX_BLAKE:
				sph_blake512_init(&ctx_blake);
				sph_blake512(&ctx_blake, in, size);
				sph_blake512_close(&ctx_blake, hash);
			break;
			case HEX_BMW:
				sph_bmw512_init(&ctx_bmw);
				sph_bmw512(&ctx_bmw, in, size);
				sph_bmw512_close(&ctx_bmw, hash);
			break;
			case HEX_GROESTL:
				sph_groestl512_init(&ctx_groestl);
				sph_groestl512(&ctx_groestl, in, size);
				sph_groestl512_close(&ctx_groestl, hash);
			break;
			case HEX_SKEIN:
				sph_skein512_init(&ctx_skein);
				sph_skein512(&ctx_skein, in, size);
				sph_skein512_close(&ctx_skein, hash);
			break;
			case HEX_JH:
				sph_jh512_init(&ctx_jh);
				sph_jh512(&ctx_jh, in, size);
				sph_jh512_close(&ctx_jh, hash);
			break;
			case HEX_KECCAK:
				sph_keccak512_init(&ctx_keccak);
				sph_keccak512(&ctx_keccak, in, size);
				sph_keccak512_close(&ctx_keccak, hash);
			break;
			case HEX_LUFFA:
				sph_luffa512_init(&ctx_luffa);
				sph_luffa512(&ctx_luffa, in, size);
				sph_luffa512_close(&ctx_luffa, hash);
			break;
			case HEX_CUBEHASH:
				sph_cubehash512_init(&ctx_cubehash);
				sph_cubehash512(&ctx_cubehash, in, size);
				sph_cubehash512_close(&ctx_cubehash, hash);
			break;
			case HEX_SHAVITE:
				sph_shavite512_init(&ctx_shavite);
				sph_shavite512(&ctx_shavite, in, size);
				sph_shavite512_close(&ctx_shavite, hash);
			break;
			case HEX_SIMD:
				sph_simd512_init(&ctx_simd);
				sph_simd512(&ctx_simd, in, size);
				sph_simd512_close(&ctx_simd, hash);
			break;
			case HEX_ECHO:
				sph_echo512_init(&ctx_echo);
				sph_echo512(&ctx_echo, in, size);
				sph_echo512_close(&ctx_echo, hash);
			break;
			case HEX_HAMSI:
				sph_hamsi512_init(&ctx_hamsi);
				sph_hamsi512(&ctx_hamsi, in, size);
				sph_hamsi512_close(&ctx_hamsi, hash);
			break;
			case HEX_FUGUE:
				sph_fugue512_init(&ctx_fugue);
				sph_fugue512(&ctx_fugue, in, size);
				sph_fugue512_close(&ctx_fugue, hash);
			break;
			case HEX_SHABAL:
				sph_shabal512_init(&ctx_shabal);
				sph_shabal512(&ctx_shabal, in, size);
				sph_shabal512_close(&ctx_shabal, hash);
			break;
			case HEX_WHIRLPOOL:
				sph_whirlpool_init(&ctx_whirlpool);
				sph_whirlpool(&ctx_whirlpool, in, size);
				sph_whirlpool_close(&ctx_whirlpool, hash);
			break;
			case HEX_SHA512:
				sph_sha512_init(&ctx_sha512);
				sph_sha512(&ctx_sha512,(const void*) in, size);
				sph_sha512_close(&ctx_sha512,(void*) hash);
			break;
		}
		algo = (uint8_t)hash[0] % HEX_HASH_FUNC_COUNT; // select next algo
		in = (const void*) hash;
		size = 64;
	}
	memcpy(state, hash, 32);
}



