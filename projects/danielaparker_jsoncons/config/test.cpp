#include <jsoncons/json.hpp>
#include <iostream>

int main() {
    using namespace jsoncons;
    json j;
    j["hello"] = "world";
    j["answer"] = 42;
    auto parsed = json::parse("{\"foo\": [1,2,3]}\n");
    j["foo"] = parsed["foo"];
    std::cout << pretty_print(j) << "\n";
    // Keep the serialized string alive while the cursor consumes it
    std::string s = j.as<std::string>();
    json_string_cursor cur(s);
    size_t count = 0;
    for (; !cur.done(); cur.next()) {
        (void)cur.current();
        ++count;
        if (count > 1000) break;
    }
    std::cout << "events:" << count << "\n";
    return 0;
}
