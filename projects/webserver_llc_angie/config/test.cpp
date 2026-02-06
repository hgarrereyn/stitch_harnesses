#include <cstdio>

extern "C" {
#include <nginx.h>
}

int main() {
    std::printf("Using %s\n", NGINX_VER);
    return 0;
}
