#include <benchmark/benchmark.h>
#include <string>

static void BM_Trivial(benchmark::State& state) {
  for (auto _ : state) {
    std::string s = "hello";
    benchmark::DoNotOptimize(s);
  }
}
BENCHMARK(BM_Trivial);
BENCHMARK_MAIN();
