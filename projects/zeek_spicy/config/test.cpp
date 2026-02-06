#include <spicy/rt/init.h>
#include <hilti/rt/init.h>
#include <iostream>

int main() {
    hilti::rt::init();
    spicy::rt::init();
    std::cout << "Spicy runtime initialized" << std::endl;
    spicy::rt::done();
    hilti::rt::done();
    return 0;
}
