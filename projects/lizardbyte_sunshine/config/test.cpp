#include <iostream>
#include <string>
#include <sunshine/utility.h>
#include <sunshine/uuid.h>

int main() {
    auto id = uuid_util::uuid_t::generate();
    std::string s = id.string();
    if (s.size() < 10) return 1;
    std::cout << "Generated UUID: " << s << "\n";
    return 0;
}
