#include <iostream>
#include <nlohmann/json.hpp>

int main() {
    nlohmann::json j;
    j["pi"] = 3.14159;
    j["happy"] = true;
    j["answer"]["everything"] = 42;
    j["list"] = {1, 0, 2};

    // round-trip via dump/parse to exercise a bit more API
    std::string s = j.dump();
    auto j2 = nlohmann::json::parse(s);

    std::cout << j2.dump(2) << std::endl;
    return j2.is_object() ? 0 : 1;
}
