#include <cstdio>
#include <cstring>
extern "C" {
#include "llmfarm_stub.h"
}

int main(){
    const char* s = llmfarm_stub_hello();
    int v = llmfarm_stub_version();
    if (!s || std::strcmp(s, "LLMFarm") != 0) {
        std::printf("Bad stub string\n");
        return 1;
    }
    std::printf("LLMFarm stub v%d: %s\n", v, s);
    return 0;
}
