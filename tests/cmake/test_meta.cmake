list(APPEND AlgList md5 sha1 sha224 sha256 sha384 sha512 sha512_224 sha512_256 sha3_224 sha3_256 sha3_384 sha3_512)

set(test_text "hello")
set(test_text2 "how are you?")
list(APPEND test_texts ${test_text} ${test_text2})
