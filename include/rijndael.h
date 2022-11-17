/*
  libpgfe
  rijndael.h

  Advanced Encryption Standard (AES), a.k.a. Rijndael

  Copyright (c) 2022 Charles Dong
*/

#ifndef LIBPGFE_RIJNDAEL_H
#define LIBPGFE_RIJNDAEL_H

#include "generic-internal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PGFE_RIJNDAEL_BLOCK_SIZE 16
#define PGFE_RIJNDAEL_BLOCK_WORD_SIZE 4

#define PGFE_AES128_KEY_SIZE 16
#define PGFE_AES192_KEY_SIZE 24
#define PGFE_AES256_KEY_SIZE 32

#define PGFE_AES128_KEY_LENGTH 4
#define PGFE_AES192_KEY_LENGTH 6
#define PGFE_AES256_KEY_LENGTH 8

#define __PGFE_AES128_ROUND_COUNT 10
#define __PGFE_AES192_ROUND_COUNT 12
#define __PGFE_AES256_ROUND_COUNT 14

typedef uint32_t pgfe_rijndael_word_t;

struct pgfe_rijnael_ctx
{
    pgfe_rijndael_word_t s[4][PGFE_RIJNDAEL_BLOCK_WORD_SIZE];
};

#define pgfe_aes128_ctx pgfe_rijnael_ctx
#define pgfe_aes192_ctx pgfe_rijnael_ctx
#define pgfe_aes256_ctx pgfe_rijnael_ctx

#ifdef __cplusplus
}
#endif

#endif