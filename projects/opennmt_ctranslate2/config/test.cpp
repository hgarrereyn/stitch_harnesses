#include <iostream>
#include <ctranslate2/primitives.h>

int main() {
  using namespace ctranslate2;
  const int N = 5;
  float data[N];
  primitives<Device::CPU>::fill(data, 2.0f, N);
  float s = primitives<Device::CPU>::sum(data, N);
  std::cout << "sum=" << s << " expected=" << (2.0f * N) << std::endl;
  return 0;
}
