#include <cstdio>
extern "C" {
#include <iperf_api.h>
}

int main() {
    const char* ver = iperf_get_iperf_version();
    std::printf("iperf version: %s\n", ver ? ver : "unknown");

    iperf_test* t = iperf_new_test();
    if (!t) {
        std::printf("failed to create test\n");
        return 0;
    }
    if (iperf_defaults(t) < 0) {
        std::printf("iperf_defaults failed\n");
    }
    // Don't run any network activity; just exercise a bit of the API
    iperf_set_test_duration(t, 1);
    iperf_set_test_blksize(t, 1024);
    iperf_free_test(t);
    return 0;
}
