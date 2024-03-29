/*
  libpgfe
  base-encoding-internal.c

  Copyright (c) 2022-2023 Charles Dong
*/

#include "./base-encoding-internal.h"

#include <limits.h>
#include <string.h>

#include "../core/generic-internal.h"

#define __bitsz (8)

#define __mkmask(digit) (UINT8_MAX >> (__bitsz - (digit)))

size_t transform(const pgfe_encode_t input[], size_t length, uint8_t chunk_size, pgfe_encode_t out[]) {
    const pgfe_encode_t *inp = input;
    pgfe_encode_t *op = out;
    size_t low, high, mv_sz, sz_diff;

    const uint8_t chunk_mask = __mkmask(chunk_size);

    for (low = 0, high = chunk_size % __bitsz; inp - input <= length; inp++, op++) {
        if (low < high) {
            *op = ((*inp) >> (__bitsz - high)) & chunk_mask;
            inp--;
        }
        else if (!high) {
            *op = (*inp) & chunk_mask;
        }
        else {
            sz_diff = __bitsz - low;
            mv_sz = chunk_size - sz_diff;
            *op = ((*inp) & __mkmask(sz_diff)) << mv_sz;
            if (inp - input + 1 < length) {
                *op |= ((*(inp + 1)) >> (__bitsz - high)) & __mkmask(high);
            }
        }

        low = (low + chunk_size) % __bitsz;
        high = (high + chunk_size) % __bitsz;
    }

    return op - out;
}

size_t unittostr(
    size_t chunk_count, size_t unit_size, size_t bit_size, size_t alphabet_size, const char alphabet[],
    const pgfe_encode_t unit[], char out[], bool padding
) {
    char unit_s[chunk_count];
    pgfe_encode_t unit_split[chunk_count];
    int i;

    transform(unit, unit_size, bit_size, unit_split);
    for (i = 0; i < chunk_count; i++) {
        unit_s[i] = alphabet[unit_split[i]];
    }

    if (padding) {
        for (i = chunk_count - 1; i >= 0; i--) {
            if (unit_s[i] != alphabet[0]) {
                break;
            }

            unit_s[i] = alphabet[alphabet_size];
        }
    }

    memcpy(out, unit_s, chunk_count);
    return chunk_count;
}

size_t encode_base_generic(
    PGFE_BASE_PARAMS_DEF, const char alphabet[], const pgfe_encode_t input[], size_t input_length, char cs_out[]
) {
    pgfe_encode_t input_unit[unit_size];
    const pgfe_encode_t *inp = input;
    size_t i, remain;
    char *sp = cs_out;

    for (i = 0; i < input_length; i += unit_size) {
        remain = input_length - i;
        if (remain < unit_size) {
            arrinit(input_unit, unit_size);
            memcpy(input_unit, inp, remain);
        }
        else {
            memcpy(input_unit, inp, unit_size);
            remain = unit_size;
        }

        sp += unittostr(chunk_count, unit_size, bit_size, alphabet_size, alphabet, input_unit, sp, unit_size - remain);
        inp += unit_size;
    }

    *sp = 0;
    return sp - cs_out;
}

size_t
decode_base_generic(PGFE_BASE_PARAMS_DEF, pgfe_encode_t (*func)(char), const char basexx_cs[], pgfe_encode_t output[]) {
    pgfe_encode_t *op, ch, sig, o_unit[unit_size];
    const char *sp = basexx_cs;
    size_t i, j;
    uint64_t u;
    const uint8_t mask = __mkmask(bit_size);

    u = 0;
    op = output;
    while (*sp) {
        for (i = 0; *sp && i < chunk_count; sp++) {
            ch = func(*sp);
            sig = ch & 0xC0;

            if (sig == UNKNOWN_CODE) {
                continue;
            }

            u = (u << bit_size) | (ch & mask);

            i++;
        }

        if (!*sp && i < chunk_count) {
            u <<= bit_size * (chunk_count - i);
        }

        for (j = 0; j < unit_size; j++) {
            o_unit[j] = (pgfe_encode_t)((u >> (__bitsz * (unit_size - j - 1))) & 0xFF);
        }

        memcpy(op, o_unit, unit_size);
        op += unit_size;
    }

    // Determine end of the output
    op -= unit_size;
    for (i = 0; i < unit_size && op[i] == o_unit[i] && op[i]; i++)
        ;

    op += i;
    *op = 0;
    return op - output;
}