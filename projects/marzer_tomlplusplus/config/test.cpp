#include <iostream>
#include <toml++/toml.hpp>

int main() {
    // Construct a small TOML table and print it
    toml::table tbl;
    tbl.insert_or_assign("library", toml::table{{"name", "toml++"}, {"version", 3}});
    tbl.insert_or_assign("features", toml::array{ "header-only", "json", "yaml" });

    std::cout << tbl << "\n";

    // Access a value via node API
    if (auto lib = tbl["library"].as_table()) {
        auto name = (*lib)["name"].value_or<std::string>("unknown");
        std::cout << "Library name: " << name << "\n";
    }
    return 0;
}
