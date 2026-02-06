#include <CLI/CLI.hpp>
#include <iostream>

int main() {
    CLI::App app{"CLI11 test app"};
    bool flag = false;
    int value = 0;
    app.add_flag("-f,--flag", flag, "A sample flag");
    app.add_option("-v,--value", value, "A sample integer option");

    // Parse empty args (program name only) to ensure basic functionality
    const char* argv[] = {"prog"};
    int argc = 1;
    try {
        app.parse(argc, const_cast<char**>(argv));
    } catch(const CLI::ParseError &e) {
        return app.exit(e);
    }

    std::cout << "Flag: " << (flag ? "true" : "false") << ", Value: " << value << "\n";
    return 0;
}
