#include <iostream>
#include <cstring>
extern "C" {
#include "encoding.h"
}

int main() {
    const char *data = "hello world";
    char buf[512] = {0};
    // Build a DNS-style hostname using base32 encoding into example.com
    int used = build_hostname(buf, sizeof(buf), data, strlen(data), "example.com", &base32_ops, 255);
    std::cout << "Encoded hostname length: " << used << "\n";
    std::cout << "Hostname: " << buf << "\n";

    // Test dotify/undotify helpers
    char tmp[128] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
    int newlen = inline_dotify(tmp, sizeof(tmp));
    int restored = inline_undotify(tmp, newlen);
    std::cout << "Dotified length: " << newlen << ", restored length: " << restored << "\n";

    return 0;
}
