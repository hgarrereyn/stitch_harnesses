#include <cstdio>
#include <cstdint>
#include <cstring>
#include <vector>

extern "C" {
#include <sha1.h>
#include <hmac.h>
#include <base32.h>
}

int main() {
  // Test SHA1 on a known input
  const char* msg = "abc";
  uint8_t digest[20];
  SHA1_INFO ctx; 
  sha1_init(&ctx);
  sha1_update(&ctx, reinterpret_cast<const uint8_t*>(msg), (int)strlen(msg));
  sha1_final(&ctx, digest);

  // Simple HMAC-SHA1
  const char* key = "key";
  const char* data = "data";
  uint8_t hmac_out[20];
  hmac_sha1(reinterpret_cast<const uint8_t*>(key), (int)strlen(key),
            reinterpret_cast<const uint8_t*>(data), (int)strlen(data),
            hmac_out, 20);

  // Base32 encode a short string
  const char* b32in = "foo";
  uint8_t b32out[64] = {0};
  int enc_len = base32_encode(reinterpret_cast<const uint8_t*>(b32in), (int)strlen(b32in), b32out, sizeof(b32out));

  // Base32 decode back
  uint8_t b32dec[64] = {0};
  int dec_len = base32_decode(b32out, b32dec, sizeof(b32dec));

  // Print a couple of bytes so the program does something observable
  printf("SHA1[0]=%02x, HMAC[0]=%02x, B32 enc len=%d, dec len=%d, first dec char=%c\n",
         digest[0], hmac_out[0], enc_len, dec_len, (dec_len>0? (char)b32dec[0] : '?'));
  return 0;
}
