#include <iostream>
#include "pika_version.h"

int main() {
    std::cout << "PikiwiDB version: " << PIKA_MAJOR << "." << PIKA_MINOR << "." << PIKA_PATCH << "\n";
    return 0;
}
