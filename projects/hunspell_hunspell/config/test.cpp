#include <hunspell.hxx>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
    // Create minimal Hunspell dictionary files
    const char* aff = "/tmp/min.aff";
    const char* dic = "/tmp/min.dic";

    {
        std::ofstream a(aff);
        a << "SET UTF-8\n"; // minimal required setting
    }
    {
        std::ofstream d(dic);
        d << 1 << "\n";
        d << "hello\n"; // single valid word
    }

    try {
        Hunspell hs(aff, dic);
        bool ok1 = hs.spell(std::string("hello"));
        bool ok2 = hs.spell(std::string("world"));
        std::cout << "hello ok=" << ok1 << " world ok=" << ok2 << "\n";
        auto sugg = hs.suggest(std::string("wrld"));
        std::cout << "suggestions=" << sugg.size() << "\n";
    } catch (...) {
        std::cout << "Exception creating or using Hunspell" << std::endl;
        return 1;
    }
    return 0;
}
