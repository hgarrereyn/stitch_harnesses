#include <iostream>
#include <cstring>
#include "filesystem_utils.h"

int main() {
    std::string name = "example.data.txt";
    std::string ext = get_file_extension(name);
    std::string base = get_file_name_without_extension(name);
    std::cout << "ext=" << ext << ", base=" << base << "\n";
    std::vector<std::string> entries;
    // list current directory (should succeed)
    list_directory(std::string("."), entries);
    std::cout << "listed " << entries.size() << " entries\n";
    return 0;
}
