#include <cstdio>
#include <cstring>
extern "C" {
#include "ada_c.h"
}

int main() {
  const char* input = "https://user:pass@example.com:8080/path?query#frag";
  ada_url url = ada_parse(input, strlen(input));
  if (!ada_is_valid(url)) {
    std::puts("parse failed");
    return 1;
  }
  ada_string host = ada_get_host(url);
  ada_string protocol = ada_get_protocol(url);
  std::printf("%.*s\n%.*s\n", (int)protocol.length, protocol.data, (int)host.length, host.data);
  ada_free(url);
  return 0;
}
