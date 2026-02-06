#include <iostream>
#include <string>
#include <json/json11.hpp>

int main() {
    using namespace json11;
    std::string err;
    const char* src = R"({"hello": "world"})";
    Json j = Json::parse(src, err);
    if (!err.empty()) {
        std::cout << "Parse error: " << err << "\n";
        return 1;
    }
    std::cout << j["hello"].string_value() << "\n";
    return 0;
}
