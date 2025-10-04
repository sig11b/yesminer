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

#include "yespower-1.0.1/yespower-pow.h"

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
		// yescrypt has a variable pers created from the data
		// see also scanhash_yespower() below
		params.version = YESPOWER_0_5;
		params.N = 2048;
		params.r = 8;
		params.pers = (const uint8_t*) "this will be overwritten in scanhash_yespower()";
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
	case ALGO_YESPOWER_BLAKE256:
		params.version = YESPOWER_1_0_BLAKE256;
		params.N = 2048;
		params.r = 32;
		params.pers = NULL;
		break;
	case ALGO_YESPOWER_EQPAY:
		params.version = YESPOWER_1_0;
		params.N = 2048;
		params.r = 32;
		params.pers = (const uint8_t*) "The gods had gone away, and the ritual of the religion continued senselessly, uselessly.";
		break;
	case ALGO_YESPOWER_ITCHAIN:
		params.version = YESPOWER_1_0;
		params.N = 1024;
		params.r = 8;
		params.pers = NULL;
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
	case ALGO_YESPOWER_ITCOIN:
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
		params.version = YESPOWER_1_0_BLAKE2B;
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
		uint32_t u32[46];
	} data = { 0 };
	union {
		yespower_binary_t yb;
		uint32_t u32[7];
	} hash;
	uint32_t n = pdata[19] - 1;
	const uint32_t Htarg = ptarget[7];
	int i;
	bool received_eqp_roots = false;
// For EQPAY, the extra data is the following:
// - the uint256 hashStateRoot and the uint256 hashUTXORoot
//   So far this is a constant. Converted into the correct endianness, this
//   constant is the one stored in eqproots[] below.
//   However, the stratum may send these roots, so we allow for flexible roots.
// - a prevoutStake "COutPoint (=uint256, uint32)" for the PoW block.
//   For PoW this will be a uint256 set to zero and a uint32 set to
//   SEQUENCE_FINAL=0xffffffff
//   This will be enforced (mostly via initialization), independently if stratum
//   sends the full extra data or not (see util.c for details on how anything
//   beyond 64 bytes is discarded).
// - a PoS/delegate unsigned char for the PoW block set to 0x00
//   Enforced as prevoutStake above.
// See also eqpay's source: src/primitives/block.h src/primitives/transaction.h
	uint8_t eqproots[] = { 0xb8,0x42,0xea,0x73,
	                       0xbe,0x5f,0xb5,0x92,
	                       0xf1,0x34,0x70,0xf9,
	                       0xcc,0x31,0xb9,0x26,
	                       0xf5,0x0f,0x19,0x1c,
	                       0x7e,0x8c,0xec,0x8f,
	                       0x7e,0xe9,0xdb,0xcc,
	                       0xcd,0x02,0x38,0x1c,
	                       0x56,0xe8,0x1f,0x17,
	                       0x1b,0xcc,0x55,0xa6,
	                       0xff,0x83,0x45,0xe6,
	                       0x92,0xc0,0xf8,0x6e,
	                       0x5b,0x48,0xe0,0x1b,
	                       0x99,0x6c,0xad,0xc0,
	                       0x01,0x62,0x2f,0xb5,
	                       0xe3,0x63,0xb4,0x21 };
//	                       0x00,0x00,0x00,0x00,
//	                       0x00,0x00,0x00,0x00,
//	                       0x00,0x00,0x00,0x00,
//	                       0x00,0x00,0x00,0x00,
//	                       0x00,0x00,0x00,0x00,
//	                       0x00,0x00,0x00,0x00,
//	                       0x00,0x00,0x00,0x00,
//	                       0x00,0x00,0x00,0x00,
//	                       0xff,0xff,0xff,0xff,
//	                       0x00 };

	for (i = 0; i < 19; i++)
		be32enc(&data.u32[i], pdata[i]);

	if (opt_algo == ALGO_YESPOWER_EQPAY) {
//		memcpy(&data.u32[20], eqproots, 101);
//		memcpy(&data.u32[20], eqproots, 64);
		for (i = 20; i < 36; i++) {
			be32enc(&data.u32[i], pdata[i]);
			if (pdata[i]) received_eqp_roots = true; // i.e. false when all are zero
		}
		if (!received_eqp_roots) {
			if (opt_debug)
				applog(LOG_DEBUG,"scanhash_yespower for EQPAY: "
				       "falling back to using hard coded root defaults.");
			memcpy(&data.u32[20], eqproots, 64);
		}
		if (opt_debug) {
			char s[129];
			bin2hex(s, (unsigned char *)&data.u32[20], 64);
			applog(LOG_DEBUG,"scanhash_yespower: added EQPAY roots: %s", s);
		}
		// the only non-zero part of the COutPoint:
		data.u32[44] = 0xffffffff;
	}

	do {
		be32enc(&data.u32[19], ++n);

		if (opt_algo == ALGO_YESCRYPT) {
		// a specialty of the coins that call their algo yescrypt
			params.pers = (const uint8_t*) data.u8;
			//params.pers = data.u8;
			params.perslen = 80;
		}

		if (opt_algo == ALGO_YESPOWER_POWER2B || opt_algo == ALGO_YESPOWER_BLAKE256) {
			if (yespower_tls_blake(data.u8, 80, &params, &hash.yb))
				abort();
		} else {
			if (yespower_tls(data.u8, opt_algo==ALGO_YESPOWER_EQPAY ? 181 : 80 ,
				         &params, &hash.yb))
				abort();
		}

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
