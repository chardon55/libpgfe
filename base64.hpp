/*
  libpgfe
  base64.hpp

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

#ifndef LIBPGFE_BASE64_HPP
#define LIBPGFE_BASE64_HPP
#ifdef __cplusplus

#include "abstract_base_encoding.hpp"

namespace chardon55 {
namespace PGFE {

class Base64 : public AbstractBaseEncoding
{
  private:
    bool _url_safe_mode;

  protected:
    void init_base_function(base_encode_func *&, base_decode_func *&);
    void init_size(base_short_size_t &, base_short_size_t &, base_short_size_t &, base_short_size_t &);

  public:
    Base64(bool url_safe_mode = false);

    bool is_url_safe_mode() {
        return _url_safe_mode;
    }
};

} // namespace PGFE
} // namespace chardon55

#endif
#endif