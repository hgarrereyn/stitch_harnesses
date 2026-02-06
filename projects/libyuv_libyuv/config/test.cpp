#include <iostream>
#include <vector>
#include <cstring>
#include "libyuv.h"

int main() {
  const int width = 2;
  const int height = 2;
  const int y_stride = width;
  const int u_stride = 1;
  const int v_stride = 1;

  std::vector<uint8_t> y(y_stride * height);
  std::vector<uint8_t> u(u_stride * (height/2));
  std::vector<uint8_t> v(v_stride * (height/2));

  std::fill(y.begin(), y.end(), 128);
  std::fill(u.begin(), u.end(), 128);
  std::fill(v.begin(), v.end(), 128);

  const int dst_stride = width * 4;
  std::vector<uint8_t> argb(dst_stride * height);

  int ret = libyuv::I420ToARGB(y.data(), y_stride,
                               u.data(), u_stride,
                               v.data(), v_stride,
                               argb.data(), dst_stride,
                               width, height);
  if (ret != 0) {
    std::cerr << "I420ToARGB failed with code: " << ret << std::endl;
    return 1;
  }

  std::cout << "ARGB[0]="
            << (int)argb[0] << "," << (int)argb[1] << "," << (int)argb[2] << "," << (int)argb[3]
            << std::endl;
  return 0;
}
