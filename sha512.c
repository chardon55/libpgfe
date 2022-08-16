#include "sha2.h"
#include "templates.c"

__PGFE_FRONTEND_GEN(sha512, sha512);
__PGFE_FRONTEND_DEFAULT_GEN(sha512, PGFE_SHA512_DIGEST_SIZE);

__PGFE_FRONTEND_GEN(sha512_224, sha512_224);
__PGFE_FRONTEND_DEFAULT_GEN(sha512_224, PGFE_SHA512_DIGEST_SIZE);

__PGFE_FRONTEND_GEN(sha512_256, sha512_256);
__PGFE_FRONTEND_DEFAULT_GEN(sha512_256, PGFE_SHA512_DIGEST_SIZE);