#include <iostream>
#include <args.hxx>

int main(int argc, char** argv) {
    args::ArgumentParser parser("Tiny test");
    args::HelpFlag help(parser, "help", "Show help", {'h', "help"});
    args::Flag simple(parser, "simple", "Simple flag", {'s', "simple"});
    try {
        parser.ParseCLI(argc, argv);
    } catch (const args::Help&) {
        std::cout << parser;
        return 0;
    } catch (const args::Error& e) {
        std::cerr << e.what() << "\n" << parser;
        return 1;
    }
    if (simple) {
        std::cout << "simple set\n";
    } else {
        std::cout << "no flags\n";
    }
    return 0;
}
