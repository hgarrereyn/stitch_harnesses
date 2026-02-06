#include "MPC/mpc.h"
#include <iostream>

int main() {
    mpcc::MPC m; // default constructor
    mpcc::State x0; x0.setZero();
    std::cout << "Constructed MPCC and zero state.\n";
    return 0;
}
