/*
  libpgfe
  base16.c

  Copyright (c) 2022-2023 Charles Dong
*/

#include "libpgfe/base_encoding/base16.h"

#include "./base-encoding-internal.h"

// Base 16 alphabet
const char BASE16_ALPHABET[] = "0123456789ABCDEF"
                               "0"; // Compatibility addition

inline pgfe_encode_t decode_base16_char(char base16_c) {
    pgfe_encode_t o;

    if (base16_c >= '0' && base16_c <= '9') {
        o = base16_c - '0';
    }
    else if (base16_c >= 'A' && base16_c <= 'F') {
        o = base16_c - 'A' + 10;
    }
    else if (base16_c >= 'a' && base16_c <= 'f') {
        o = base16_c - 'a' + 10;
    }
    else {
        o = UNKNOWN_CODE;
    }

    return o;
}

inline size_t pgfe_encode_base16(const pgfe_encode_t input[], size_t input_length, char cs_out[]) {
    return encode_base_generic(PGFE_BASE_PARAMS(BASE16), BASE16_ALPHABET, input, input_length, cs_out);
}

size_t pgfe_decode_base16(const char base16_cs[], pgfe_encode_t output[]) {
    return decode_base_generic(PGFE_BASE_PARAMS(BASE16), decode_base16_char, base16_cs, output);
}