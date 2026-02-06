#include <WeChatHelper/Function.h>
#include <iostream>

int main() {
    // Call the stubbed API functions to ensure linkage works
    wchar_t wxid[] = L"wxid_example";
    wchar_t msg[] = L"hello";
    AddWxUser(wxid, msg);
    AntiRevoke();
    OpenUrl((wchar_t*)L"https://example.com");
    std::wcout << L"WeChatRobot stub API invoked successfully" << std::endl;
    return 0;
}
