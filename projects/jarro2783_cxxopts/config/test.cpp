#include <iostream>
#include <vector>
#include <string>
#include <cxxopts.hpp>

int main(int argc, char** argv) {
    try {
        cxxopts::Options options("testprog", "Test program for cxxopts");
        options.add_options()
            ("h,help", "Print help")
            ("i,integer", "An integer option", cxxopts::value<int>()->default_value("42"))
            ("s,string", "A string option", cxxopts::value<std::string>()->default_value("hello"));

        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help() << std::endl;
        }
        int i = result["integer"].as<int>();
        std::string s = result["string"].as<std::string>();
        // Use the values to avoid optimizing away
        std::cout << "i=" << i << ", s=" << s << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
