#include <lsfg-vk-backend/lsfgvk.hpp>
#include <iostream>

int main() {
    // Call a simple API to ensure the library links
    lsfgvk::backend::makeLeaking();
    try {
        throw lsfgvk::backend::error("test error");
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }
    return 0;
}
