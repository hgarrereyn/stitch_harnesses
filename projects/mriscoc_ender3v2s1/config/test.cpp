#include <cstdio>
#include <cstdint>
#include <cstring>
#include <crc16.h>

int main() {
  const char *msg = "hello world";
  uint16_t crc = 0xFFFF;
  crc16(&crc, msg, (uint16_t)strlen(msg));
  // Print the CRC to ensure the function is linked and executed
  std::printf("CRC16('%s')=0x%04X\n", msg, crc);
  return 0;
}
