#include <hermes/Public/RuntimeConfig.h>
#include <hermes/Public/CtorConfig.h>
#include <iostream>

int main() {
  using namespace hermes::vm;
  RuntimeConfig cfg = RuntimeConfig::Builder()
      .withEnableEval(true)
      .withEnableGenerator(true)
      .withNativeStackGap(1024)
      .build();

  std::cout << "EnableEval=" << (cfg.getEnableEval() ? 1 : 0)
            << ", EnableGenerator=" << (cfg.getEnableGenerator() ? 1 : 0)
            << ", NativeStackGap=" << cfg.getNativeStackGap()
            << std::endl;
  return 0;
}
