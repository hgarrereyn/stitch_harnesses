#include <unifex/just.hpp>
#include <unifex/sync_wait.hpp>
#include <iostream>

int main() {
    auto result = unifex::sync_wait(unifex::just(123));
    if (result) {
        std::cout << "libunifex ok: " << *result << std::endl;
    } else {
        std::cout << "libunifex returned no value" << std::endl;
    }
    return 0;
}
