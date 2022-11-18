/*
  libpgfe
  rijndael.c

  Advanced Encryption Standard (AES), a.k.a. Rijndael

  Copyright (c) 2022 Charles Dong
*/

#include "rijndael.h"

static inline void __sub_bytes(struct pgfe_rijnael_ctx *ctx) {}

static inline void __shift_rows(struct pgfe_rijnael_ctx *ctx) {}

static inline void __mix_columns(struct pgfe_rijnael_ctx *ctx) {}

static inline void __add_round_key(struct pgfe_rijnael_ctx *ctx, pgfe_rijndael_word_t w[]) {}