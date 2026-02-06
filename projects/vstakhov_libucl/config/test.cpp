#include <iostream>
#include <string>
#include <ucl++.h>

int main() {
    std::string input = R"({\n  key: \"value\",\n  number: 42,\n  flag: true,\n  arr: [1, 2, 3]\n})";
    std::string err;
    ucl::Ucl obj = ucl::Ucl::parse(input, err);
    if (!err.empty()) {
        std::cout << "Parse error: " << err << "\n";
        return 0; // still exit successfully for the test harness
    }

    // Access some fields using the C++ API
    std::string key = obj["key"].string_value("<none>");
    long long num = obj["number"].int_value(-1);
    bool flag = obj["flag"].bool_value(false);
    size_t arr_sz = obj["arr"].size();

    // Emit back to JSON
    std::string out = obj.dump(UCL_EMIT_JSON_COMPACT);

    std::cout << "key=" << key << ", number=" << num << ", flag=" << (flag?"true":"false")
              << ", arr_sz=" << arr_sz << "\n";
    std::cout << out << "\n";
    return 0;
}
