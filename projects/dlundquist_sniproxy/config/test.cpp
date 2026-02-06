#include <cstdio>
extern "C" {
#include "sniproxy/logger.h"
}

int main() {
    // Use the logging API; this should print to stderr via the default logger
    warn("sniproxy test: %s %d", "hello", 42);
    info("sniproxy info message");
    debug("sniproxy debug message");
    return 0;
}
