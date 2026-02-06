#include <cstdio>
#include <tag.hpp>

extern "C" long utf8_strlen(const char*);

int main() {
    // Use a small C++ API header
    ff::Tag tag("TEST");
    const char* s = static_cast<const char*>(tag);
    std::printf("Tag: %s\n", s);

    // Call a libfontforge function to ensure linking works
    long n = utf8_strlen("héllo");
    std::printf("utf8_strlen(\"héllo\") = %ld\n", n);
    return 0;
}
