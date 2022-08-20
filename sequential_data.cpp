/*
  libpgfe
  sequential_data.cpp

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

#include "sequential_data.hpp"

#include <cstring>

using namespace chardon55::PGFE;

SequentialData::~SequentialData() {
    if (seq) {
        delete seq;
    }

    if (hex_str) {
        delete hex_str;
    }
}

SequentialData::SequentialData(const pgfe_encode_t *pgfe_seq, size_t length) {
    seq = new pgfe_encode_t[length + 1];
    memcpy(seq, pgfe_seq, length);
    seq[length] = 0;
    sz = length;
}

SequentialData::SequentialData(const char *cs) : SequentialData((const pgfe_encode_t *)cs, strlen(cs)) {
    _is_str = true;
}

SequentialData::SequentialData(std::string &cpp_s)
    : SequentialData((const pgfe_encode_t *)cpp_s.c_str(), cpp_s.length()) {
    _is_str = true;
}

size_t SequentialData::length() {
    return sz;
}

const char *SequentialData::to_cs() {
    return (const char *)seq;
}

std::string SequentialData::to_str() {
    std::string s((char *)seq);
    return s;
}

const char *SequentialData::to_hex_cs() {
    if (!hex_str) {
        hex_sz = sz * 2;
        hex_str = new char[hex_sz + 1];
    }

    pgfe_hash_to_hex_string(seq, sz, hex_str);
    return hex_str;
}

std::string SequentialData::to_hex_str() {
    std::string s(to_hex_cs());
    return s;
}

const pgfe_encode_t *SequentialData::to_pgfe_seq() {
    return seq;
}

const pgfe_encode_t *SequentialData::to_pgfe_seq(size_t &length_out) {
    length_out = sz;
    return to_pgfe_seq();
}

bool SequentialData::is_str() {
    return _is_str;
}