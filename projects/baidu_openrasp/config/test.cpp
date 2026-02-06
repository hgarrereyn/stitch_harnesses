#include <json.hpp>
#include <iostream>
using nlohmann::json;
int main() {
    json j;
    j["project"] = "openrasp";
    j["numbers"] = {1,2,3};
    j["active"] = true;
    std::cout << j.dump() << "\n";
    return 0;
}
