#include <iostream>
#include "api/app/app.h"

int main() {
    unsigned int pid = app::getProcessId();
    std::cout << "PID: " << pid << std::endl;
    return 0;
}
