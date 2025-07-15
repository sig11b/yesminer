/*-
 * Copyright 2009 Colin Percival
 * Copyright 2012-2025 Alexander Peslyak
 * Copyright 2025 Sig11@github
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
 * This file is based on portions of yespower-opt.c by Alexander Peslyak.
 *
 */

/*
 * Including "yespower-opt.c" seems to be an ugly solution. However,
 * that way, solardiz's upstream version remains unchaged and an update
 * can be dropped in without worrying too much.
 */

#include "yespower-opt.c"
#include "yespower-pow.h"

/**
 * yespower_blake(local, src, srclen, params, dst):
 * Compute yespower(src[0 .. srclen - 1], N, r), to be checked for "< target".
 * local is the thread-local data structure, allowing to preserve and reuse a
 * memory allocation across calls, thereby reducing its overhead.
 *
 * Return 0 on success; or -1 on error.
 */
int yespower_blake(yespower_local_t *local,
    const uint8_t *src, size_t srclen,
    const yespower_params_t *params,
    yespower_binary_t *dst)
{
	yespower_blake_version_t version = (yespower_blake_version_t)params->version;
	uint32_t N = params->N;
	uint32_t r = params->r;
	const uint8_t *pers = params->pers;
	size_t perslen = params->perslen;
	uint32_t Swidth;
	size_t B_size, V_size, XY_size, need;
	uint8_t *B, *S;
	salsa20_blk_t *V, *XY;
	pwxform_ctx_t ctx;
	uint8_t blake[32];

	/* Sanity-check parameters */
	if ((version != YESPOWER_1_0_BLAKE2B && version != YESPOWER_1_0_BLAKE256) ||
	    N < 1024 || N > 512 * 1024 || r < 8 || r > 32 ||
	    (N & (N - 1)) != 0 ||
	    (!pers && perslen)) {
		errno = EINVAL;
		goto fail;
	}

	/* Allocate memory */
	B_size = (size_t)128 * r;
	V_size = B_size * N;
	// (if variant) is the same for all so far.
		XY_size = B_size + 64;
		Swidth = Swidth_1_0;
		ctx.Sbytes = 3 * Swidth_to_Sbytes1(Swidth);
	need = B_size + V_size + XY_size + ctx.Sbytes;
	if (local->aligned_size < need) {
		if (free_region(local))
			goto fail;
		if (!alloc_region(local, need))
			goto fail;
	}
	B = (uint8_t *)local->aligned;
	V = (salsa20_blk_t *)((uint8_t *)B + B_size);
	XY = (salsa20_blk_t *)((uint8_t *)V + V_size);
	S = (uint8_t *)XY + XY_size;
	ctx.S0 = S;
	ctx.S1 = S + Swidth_to_Sbytes1(Swidth);

	if (version == YESPOWER_1_0_BLAKE2B)
		blake2b_hash(blake, src, srclen);
	else
		blake256_hash(blake, src, srclen);

	ctx.S2 = S + 2 * Swidth_to_Sbytes1(Swidth);
	ctx.w = 0;

	if (pers) {
		src = pers;
		srclen = perslen;
	} else {
		srclen = 0;
	}

	if (version == YESPOWER_1_0_BLAKE2B) {
		pbkdf2_blake2b(blake, sizeof(blake), src, srclen, 1, B, 128);
		memcpy(blake, B, sizeof(blake));
		smix_1_0(B, r, N, V, XY, &ctx);
		hmac_blake2b_hash((uint8_t *)dst, B + B_size - 64, 64,
		    blake, sizeof(blake));
	} else {
		pbkdf2_blake256(blake, sizeof(blake), src, srclen, 1, B, 128);
		memcpy(blake, B, sizeof(blake));
		smix_1_0(B, r, N, V, XY, &ctx);
		hmac_blake256_hash((uint8_t *)dst, B + B_size - 64, 64,
		    blake, sizeof(blake));
	}

	/* Success! */
	return 0;

fail:
	memset(dst, 0xff, sizeof(*dst));
	return -1;
}

/**
 * yespower_tls_blake(src, srclen, params, dst):
 * Compute yespower(src[0 .. srclen - 1], N, r), to be checked for "< target".
 * The memory allocation is maintained internally using thread-local storage.
 *
 * Return 0 on success; or -1 on error.
 */
int yespower_tls_blake(const uint8_t *src, size_t srclen,
    const yespower_params_t *params, yespower_binary_t *dst)
{
#ifdef _MSC_VER
	static __declspec(thread) int initialized = 0;
	static __declspec(thread) yespower_local_t local;
#else
	static __thread int initialized = 0;
	static __thread yespower_local_t local;
#endif

	if (!initialized) {
		init_region(&local);
		initialized = 1;
	}

	return yespower_blake(&local, src, srclen, params, dst);
}

