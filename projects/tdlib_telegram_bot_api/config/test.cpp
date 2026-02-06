#include <cstdio>
#include <cstring>
#include "telegram-bot-api.h"

int main(){
    const char* v = tbapi_version();
    if(!v || std::strlen(v)==0){
        std::puts("No version");
        return 1;
    }
    std::printf("Stub Telegram Bot API version: %s\n", v);
    return 0;
}
