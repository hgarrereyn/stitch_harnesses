#include <iostream>
#include "fuzz/host/hypercall/types.h"

int main() {
    bad_state st = RUNNING_AFTER_CONTINUATION;
    log_subsystem sub = THREAD;
    std::cout << "bad_state=" << (int)st << ", log_subsystem=" << (int)sub << "\n";
    return 0;
}
