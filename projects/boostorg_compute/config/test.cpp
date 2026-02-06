#include <iostream>
#include <vector>
#include <boost/compute/system.hpp>
#include <boost/compute/platform.hpp>

namespace compute = boost::compute;

int main() {
    try {
        std::vector<compute::platform> plats = compute::system::platforms();
        std::cout << "Found platforms: " << plats.size() << "\n";
        if(!plats.empty()){
            std::cout << "First platform name length: " << plats.front().name().size() << "\n";
        }
    } catch(const std::exception &e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
    return 0;
}
