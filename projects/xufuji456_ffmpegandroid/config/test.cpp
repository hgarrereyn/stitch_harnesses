#include <iostream>
#include <string>
#include <nextcommon/NextLog.h>
#include <nextcommon/NextDictionary.h>

int main() {
    SetLogLevel(AV_LEVEL_DEBUG);
    NEXT_LOGI("Test", "Hello %s %d", "World", 42);

    NextDictionary dict;
    dict.SetInt64("answer", 42);
    dict.SetString("greeting", std::string("hello"));

    int64_t v = dict.GetInt64("answer", -1);
    std::string s = dict.GetString("greeting", nullptr);

    std::cout << "answer=" << v << ", greeting=" << s << std::endl;
    return 0;
}
