/*
  libpgfe
  generic-internal.c

  Copyright (c) 2022-2023 Charles Dong
*/

#include "./generic-internal.h"

#include <string.h>

inline void arrinit(pgfe_encode_t arr[], size_t size) {
    memset(arr, 0, size);
}

inline void arrcpy(pgfe_encode_t dest[], size_t dest_s, const pgfe_encode_t src[], size_t src_s) {
    size_t cpy_s = dest_s > src_s ? src_s : dest_s;
    memcpy(dest, src, cpy_s);
    arrinit(dest + cpy_s, dest_s - cpy_s);
}

inline void ch2hex(char ch, pgfe_encode_t *hex) {
    pgfe_encode_t tmp_o = 0;
    if (ch >= '0' && ch <= '9') {
        tmp_o = ch - '0';
    }
    else if (ch >= 'A' && ch <= 'F') {
        tmp_o = ch - 'A' + 10;
    }
    else if (ch >= 'a' && ch <= 'f') {
        tmp_o = ch - 'a' + 10;
    }
    else {
        tmp_o = PGFE_HEX_UNKNOWN_CHAR;
    }

    *hex = tmp_o;
}

void reverse(pgfe_encode_t *low, pgfe_encode_t *high) {
    pgfe_encode_t tmp;

    for (; low < high; low++, high--) {
        tmp = *low;
        *low = *high;
        *high = tmp;
    }
}