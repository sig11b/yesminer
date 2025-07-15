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
 * This file is based on portions of yespower.h by Alexander Peslyak.
 *
 */

#include "yespower.h"
#include "blake2b.h"
#include "blake256.h"

/*
 * the below enum is not only ugly, but also dangerous. The indivudal
 * values MUST NOT be any of the "type enum yespower_version_t" defined
 * in yespower.h
 * The advantage is that solardiz's upstream yespower can be used
 * without modification
 */

typedef enum { YESPOWER_1_0_BLAKE2B = -1000, YESPOWER_1_0_BLAKE256 = -1001 } yespower_blake_version_t;

extern int yespower_tls_blake(const uint8_t *src, size_t srclen,
    const yespower_params_t *params, yespower_binary_t *dst);

