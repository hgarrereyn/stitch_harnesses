#include <iostream>
#include <weechat/weechat-plugin.h>

int main() {
    const char* api_ver = WEECHAT_PLUGIN_API_VERSION;
    std::cout << "WeeChat plugin API version: " << api_ver << "\n";
    std::cout << "RC_OK=" << WEECHAT_RC_OK << ", RC_ERROR=" << WEECHAT_RC_ERROR << "\n";
    int t = WEECHAT_HDATA_STRING;
    std::cout << "Sample hdata type value: " << t << "\n";
    return 0;
}
