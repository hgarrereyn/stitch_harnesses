#include <iostream>
#include "civetweb.h"

int main() {
    unsigned f = mg_init_library(0);
    std::cout << "CivetWeb init features: " << f << "\n";
    mg_exit_library();
    return 0;
}
