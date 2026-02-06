#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include "aixed_wechat_hook/Utils.h"

int main() {
    std::string s = "Hello, 微信Hook!";
    std::wstring ws = String2WString(s);
    std::wcout << L"WString length: " << ws.size() << L"\n";
    if (!ws.empty()) {
        std::wcout << L"First char code: " << static_cast<int>(ws[0]) << L"\n";
    }
    return 0;
}
