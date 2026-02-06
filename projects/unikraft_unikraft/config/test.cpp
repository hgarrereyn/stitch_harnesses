#include <iostream>
#include <uk/print/snprintf.h>

int main() {
    char buf[128];
    int n = uk_snprintf(buf, sizeof(buf), "Hello %s: %d + %d = %d", "Unikraft", 2, 3, 2+3);
    if (n < 0) {
        std::cout << "snprintf failed\n";
        return 1;
    }
    std::cout << buf << " (len=" << n << ")\n";
    return 0;
}
