#include <iostream>
#include "acl_cpp/lib_acl.hpp"

int main() {
    // Simple use of acl::string from lib_acl_cpp
    acl::string s = "hello acl!";
    s += " ";
    s.append("cpp");
    std::cout << s.c_str() << std::endl;

    // Build a small JSON object using acl::json
    acl::json j;                 // empty json
    acl::json_node& root = j.get_root();
    root.add_text("key", "value");

    acl::string out;
    j.build_json(out);
    std::cout << out.c_str() << std::endl;

    return 0;
}
