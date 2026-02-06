#include <iostream>
#include <filesystem>
#include <string>
#include "MMKV.h"

int main() {
    std::string rootDir = "/tmp/mmkv_root";
    std::error_code ec;
    std::filesystem::create_directories(rootDir, ec);

    MMKV::initializeMMKV(rootDir);

    MMKV* kv = MMKV::defaultMMKV();
    if (!kv) {
        std::cout << "Failed to get default MMKV instance\n";
        return 1;
    }

    kv->set(true, "bool");
    bool b = kv->getBool("bool");

    kv->set(1024, "int32");
    int i = kv->getInt32("int32");

    kv->set(std::string("Hello from MMKV"), "string");
    std::string s;
    kv->getString("string", s);

    std::cout << "bool=" << b << ", int32=" << i << ", string=" << s << "\n";
    return 0;
}
