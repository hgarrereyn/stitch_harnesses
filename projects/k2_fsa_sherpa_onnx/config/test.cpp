#include <iostream>
#include <vector>
#include <cmath>
#include "sherpa-onnx/c-api/cxx-api.h"

int main() {
  using namespace sherpa_onnx::cxx;

  // Create a short 440 Hz sine wave, 0.1 seconds at 16 kHz
  const int sr = 16000;
  const float duration = 0.1f;
  const int n = static_cast<int>(sr * duration);
  Wave w;
  w.sample_rate = sr;
  w.samples.resize(n);
  for (int i = 0; i < n; ++i) {
    w.samples[i] = 0.2f * std::sin(2.0 * M_PI * 440.0 * (i / static_cast<double>(sr)));
  }

  const std::string path = "/tmp/test_sherpa_onnx.wav";
  if (!WriteWave(path, w)) {
    std::cerr << "Failed to write wave" << std::endl;
    return 1;
  }

  Wave r = ReadWave(path);
  std::cout << "Read wave: sample_rate=" << r.sample_rate
            << ", samples=" << r.samples.size() << std::endl;

  // Basic check
  if (r.sample_rate != sr || r.samples.empty()) return 2;
  std::cout << "OK" << std::endl;
  return 0;
}
