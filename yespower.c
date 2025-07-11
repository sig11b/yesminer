/*
 * Copyright 2011 ArtForz, 2011-2014 pooler, 2018 The Resistance developers, 2020 The Sugarchain Yumekawa developers, 2025 Sig11
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is loosly based on a tiny portion of pooler's cpuminer scrypt.c.
 */

#include "cpuminer-config.h"
#include "miner.h"

#include "yespower-1.0.1/yespower.h"

#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

yespower_params_t params;

bool setup_variant()
{
	// all variants have the same difficulty conversion
	// factor of 65536. Hence, this is not set hete.
	switch (opt_algo) {
	case ALGO_YESCRYPT:
		params.version = YESPOWER_0_5;
		params.N = 2048;
		params.r = 8;
		params.pers = NULL;
		break;
	case ALGO_YESCRYPT_R8:
		params.version = YESPOWER_0_5;
		params.N = 2048;
		params.r = 8;
		params.pers = (const uint8_t*) "Client Key";
		break;
	case ALGO_YESCRYPT_R16:
		params.version = YESPOWER_0_5;
		params.N = 4096;
		params.r = 16;
		params.pers = (const uint8_t*) "Client Key";
		break;
	case ALGO_YESCRYPT_R32:
		params.version = YESPOWER_0_5;
		params.N = 4096;
		params.r = 32;
		params.pers = (const uint8_t*) "WaviBanana";
		break;
	case ALGO_YESPOWER:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 32;
		params.pers = NULL;
		break;
	case ALGO_YESPOWER_ADVC:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 32;
		params.pers = (const uint8_t*) "Let the quest begin";
		break;
	case ALGO_YESPOWER_ARWN:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 32;
		params.pers = (const uint8_t*) "ARWN";
		break;
	case ALGO_YESPOWER_CPU:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 32;
		params.pers = (const uint8_t*) "CPUpower: The number of CPU working or available for proof-of-work mining";
		break;
	case ALGO_YESPOWER_EQPAY:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 32;
		params.pers = (const uint8_t*) "The gods had gone away, and the ritual of the religion continued senselessly, uselessly.";
		break;
	case ALGO_YESPOWER_IOTS:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 32;
		params.pers = (const uint8_t*) "Iots is committed to the development of IOT";
		break;
	case ALGO_YESPOWER_ISO:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 32;
		params.pers = (const uint8_t*) "IsotopeC";
		break;
	case ALGO_YESPOWER_ITC:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 32;
		params.pers = (const uint8_t*) "InterITC";
		break;
	case ALGO_YESPOWER_LITB:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 32;
		params.pers = (const uint8_t*) "LITBpower: The number of LITB working or available for proof-of-work mining";
		break;
	case ALGO_YESPOWER_LTNCG:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 32;
		params.pers = (const uint8_t*) "LTNCGYES";
		break;
	case ALGO_YESPOWER_MGPC:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 32;
		params.pers = (const uint8_t*) "Magpies are birds of the Corvidae family.";
		break;
	case ALGO_YESPOWER_POWER2B:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 32;
		params.pers = (const uint8_t*) "Now I am become Death, the destroyer of worlds";
		break;
	case ALGO_YESPOWER_R16:
		params.version = YESPOWER_1_0;
		params.N = 4096;
		params.r = 16;
		params.pers = NULL;
		break;
	case ALGO_YESPOWER_RES:
		params.version = YESPOWER_1_0;
		params.N = 4096;
		params.r = 32;
		params.pers = NULL;
		break;
	case ALGO_YESPOWER_SUGAR:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 32;
		params.pers = (const uint8_t*) "Satoshi Nakamoto 31/Oct/2008 Proof-of-work is essentially one-CPU-one-vote";
		break;
	case ALGO_YESPOWER_TIDE:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 8;
		params.pers = NULL;
		break;
	case ALGO_YESPOWER_URX:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 32;
		params.pers = (const uint8_t*) "UraniumX";
		break;
	case ALGO_NONE:
		fprintf( stderr, "Something went wrong.\n" );
		exit(1);
	default:
		fprintf( stderr, "Unimplemented algo encountered.\n" );
		exit(1);
	};
	if (params.pers == NULL) {
		params.perslen = 0;
	} else {
		params.perslen = strlen((char*)params.pers);
	}
	return true;
}

int scanhash_yespower(int thr_id, uint32_t *pdata,
	const uint32_t *ptarget,
	uint32_t max_nonce, unsigned long *hashes_done)
{
	union {
		uint8_t u8[8];
		uint32_t u32[20];
	} data;
	union {
		yespower_binary_t yb;
		uint32_t u32[7];
	} hash;
	uint32_t n = pdata[19] - 1;
	const uint32_t Htarg = ptarget[7];
	int i;
	
	for (i = 0; i < 19; i++)
		be32enc(&data.u32[i], pdata[i]);

	do {
		be32enc(&data.u32[19], ++n);

		if (yespower_tls(data.u8, 80, &params, &hash.yb))
			abort();

		if (le32dec(&hash.u32[7]) <= Htarg) {
			for (i = 0; i < 7; i++)
				hash.u32[i] = le32dec(&hash.u32[i]);
			if (fulltest(hash.u32, ptarget)) {
				*hashes_done = n - pdata[19] + 1;
				pdata[19] = n;
				return 1;
			}
		}
	} while (n < max_nonce && !work_restart[thr_id].restart);

	*hashes_done = n - pdata[19] + 1;
	pdata[19] = n;
	return 0;
}
