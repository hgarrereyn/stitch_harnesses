#include <iostream>
#include <string>
#include <cstring>
#include <INIReader.h>
#include <ini.h>

int main() {
    const char *data = 
        "; example INI data\n"
        "[protocol]\n"
        "version=7\n"
        "\n"
        "[user]\n"
        "name=John Doe\n"
        "email=john@example.com\n";

    INIReader reader(data, std::strlen(data));
    if (reader.ParseError() < 0) {
        std::cout << "Parse error: " << reader.ParseErrorMessage() << "\n";
        return 1;
    }

    std::cout << "Version=" << reader.GetInteger("protocol", "version", -1) << "\n";
    std::cout << "Name=" << reader.Get("user", "name", "UNKNOWN") << "\n";
    std::cout << "Email=" << reader.Get("user", "email", "UNKNOWN") << "\n";

    // Also exercise the C API: parse the same buffer and count keys
    int count = 0;
    auto handler = [](void* user, const char* section, const char* name, const char* value) -> int {
        int* c = static_cast<int*>(user);
        if (section && name && value) (*c)++;
        return 1; // continue
    };

    int rc = ini_parse_string(data, handler, &count);
    std::cout << "C parsed entries=" << count << ", rc=" << rc << "\n";

    return 0;
}
