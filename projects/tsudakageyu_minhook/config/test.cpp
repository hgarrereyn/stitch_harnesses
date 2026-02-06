#include <cstdio>
#include <MinHook.h>

extern "C" const char* WINAPI MH_StatusToString(MH_STATUS status) {
    switch (status) {
        case MH_OK: return "MH_OK";
        case MH_UNKNOWN: return "MH_UNKNOWN";
        default: return "OTHER";
    }
}

int main() {
    const char* s1 = MH_StatusToString(MH_OK);
    const char* s2 = MH_StatusToString(MH_UNKNOWN);
    std::printf("%s %s\n", s1, s2);
    return 0;
}
