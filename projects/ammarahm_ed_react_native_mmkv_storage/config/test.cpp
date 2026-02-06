#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include "MMKV.h"

int main() {
    // Prepare a root directory for MMKV
    const char* root = "/tmp/mmkv_root";
    mkdir(root, 0755);

    MMKV::initializeMMKV(std::string(root));

    // Create a default instance and perform basic operations
    MMKV* kv = MMKV::defaultMMKV();
    if (!kv) {
        std::cerr << "Failed to get default MMKV instance\n";
        return 1;
    }

    kv->set(true, std::string("flag"));
    kv->set(42, std::string("answer"));
    kv->set(std::string("hello"), std::string("greet"));

    bool has;
    bool flag = kv->getBool(std::string("flag"), false, &has);
    int answer = kv->getInt32(std::string("answer"), 0, &has);
    std::string greet;
    kv->getString(std::string("greet"), greet);

    std::cout << "flag=" << flag << ", answer=" << answer << ", greet=" << greet << "\n";

    kv->sync();
    kv->close();
    MMKV::onExit();
    return 0;
}
