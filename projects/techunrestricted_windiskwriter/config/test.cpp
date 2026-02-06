#include <cstdio>
#include <cstdint>
extern "C" {
#include <wimlib.h>
#include <wimlib_tchar.h>
}
int main() {
    // Use a couple of public macros/types from the library headers
    const char *root = WIMLIB_WIM_ROOT_PATH; // "/"
    uint64_t guid_len = WIMLIB_GUID_LEN;
    // Use the tchar abstraction from wimlib_tchar.h
    tchar sample[] = T("hello");
    (void)sample;
    std::printf("root=%s guid_len=%llu\n", root, (unsigned long long)guid_len);
    return 0;
}
