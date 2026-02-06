#include "mongoose.h"
#include <stdio.h>
#include <string.h>

int main() {
  // Simple self-test: base64 encode and decode using Mongoose API
  const char *msg = "hello, mongoose";
  char enc[128];
  char dec[128];
  size_t elen = mg_base64_encode((const unsigned char*)msg, strlen(msg), enc, sizeof(enc));
  size_t dlen = mg_base64_decode(enc, elen, dec, sizeof(dec));
  // Ensure round-trip
  dec[dlen] = '\0';
  printf("enc=%s\n", enc);
  printf("dec=%s\n", dec);

  // Create and init an event manager, poll once to ensure symbols link
  struct mg_mgr mgr; 
  mg_mgr_init(&mgr);
  mg_mgr_poll(&mgr, 0);
  mg_mgr_free(&mgr);

  return (strcmp(dec, msg) == 0) ? 0 : 1;
}
