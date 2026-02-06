#include <cstdio>
#include <cstring>

#ifdef __cplusplus
#define COSMOPOLITAN_C_START_ extern "C" {
#define COSMOPOLITAN_C_END_ }
#else
#define COSMOPOLITAN_C_START_
#define COSMOPOLITAN_C_END_
#endif
#include <puff.h>

int main() {
  // Raw DEFLATE stream: final stored block containing "hello"
  const unsigned char deflate_hello[] = {0x01, 0x05, 0x00, 0xFA, 0xFF, 'h','e','l','l','o'};
  unsigned long srclen = sizeof(deflate_hello);
  unsigned char out[32];
  unsigned long outlen = sizeof(out);
  int rc = _puff(out, &outlen, deflate_hello, &srclen);
  if (rc != 0) {
    std::printf("puff failed rc=%d\n", rc);
  } else {
    std::printf("%.*s\n", (int)outlen, out);
  }
  return 0;
}
