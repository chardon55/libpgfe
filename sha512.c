/*
  libpgfe
  sha512.c

  Copyright (C) 2022 Charles Dong

  libpgfe is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/

#include "sha2.h"

#include "sha2-internal.h"
#include "templates.c"

const pgfe_word_t __pgfe_sha512_H0[] = {
    0xF3BCC908, 0x6A09E667, 0x84CAA73B, 0xBB67AE85, 0xFE94F82B, 0x3C6EF372, 0x5F1D36F1, 0xA54FF53A,
    0xADE682D1, 0x510E527F, 0x2B3E6C1F, 0x9B05688C, 0xFB41BD6B, 0x1F83D9AB, 0x137E2179, 0x5BE0CD19,
};

__PGFE_FRONTEND_GEN2(sha512)
__PGFE_FRONTEND_DEFAULT_GEN2(sha512, SHA512);

void pgfe_sha512_init(struct pgfe_sha512_ctx *ctx) {
    if (!ctx) return;

    ctx->len_low = ctx->len_high = to_pf64(0);
    ctx->index = 0;

    memcpy(ctx->state, __pgfe_sha512_H0, sizeof(ctx->state));
}

inline void pgfe_sha512_update(struct pgfe_sha512_ctx *ctx, const pgfe_encode_t input[], size_t length) {
    __pgfe_sha384n512_update(ctx, input, length);
}

inline void pgfe_sha512_digest(struct pgfe_sha512_ctx *ctx, pgfe_encode_t output[], size_t out_length) {
    __pgfe_sha384n512_digest(ctx, output, out_length, PGFE_SHA512_DIGEST_SIZE);
}

__PGFE_FRONTEND_GEN(sha512_224, sha512_224);
__PGFE_FRONTEND_DEFAULT_GEN(sha512_224, PGFE_SHA512_DIGEST_SIZE);

__PGFE_FRONTEND_GEN(sha512_256, sha512_256);
__PGFE_FRONTEND_DEFAULT_GEN(sha512_256, PGFE_SHA512_DIGEST_SIZE);