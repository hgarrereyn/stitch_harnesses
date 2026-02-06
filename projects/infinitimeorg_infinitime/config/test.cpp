#include <cstdio>
#include <cstdint>
#include <vector>
#include <InfiniTime/components/rle/RleDecoder.h>

int main() {
  const uint8_t encoded[] = {2, 1, 3, 2};
  std::vector<uint8_t> out(16);

  Pinetime::Tools::RleDecoder dec(encoded, sizeof(encoded), 0xF800, 0x07E0);
  dec.DecodeNext(out.data(), out.size());

  unsigned sum = 0;
  for (size_t i = 0; i < out.size(); ++i) sum += out[i];
  std::printf("sum=%u\n", sum);
  return 0;
}
