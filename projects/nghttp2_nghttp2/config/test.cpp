#include <cstdio>
#include <nghttp2/nghttp2.h>

int main() {
    const nghttp2_info* info = nghttp2_version(0);
    if (!info || !info->version_str) {
        return 1;
    }
    // Print a couple of version strings to exercise the API
    std::printf("nghttp2 version: %s\n", info->version_str);
    std::printf("nghttp2 proto id: %s\n", info->proto_str);

    // Use one more trivial API to ensure symbols are linked
    int rv = nghttp2_check_authority((const uint8_t*)"example.com", 11);
    std::printf("check_authority(example.com) => %d\n", rv);
    return 0;
}
