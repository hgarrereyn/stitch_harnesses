#include <iostream>
#include <sw/redis++/redis++.h>
#include <sw/redis++/version.h>

int main() {
    try {
        // Construction is lazy; it won't connect until a command is issued.
        sw::redis::Redis redis("tcp://127.0.0.1:6379");
        (void)redis; // suppress unused warning
        std::cout << "redis-plus-plus version: "
                  << sw::redis::VERSION_MAJOR << "."
                  << sw::redis::VERSION_MINOR << "."
                  << sw::redis::VERSION_PATCH << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
