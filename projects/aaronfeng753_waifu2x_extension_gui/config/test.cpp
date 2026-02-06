#include <cstdio>
#include <cstring>
#include "stubwaifu.h"

int main(){
    const char* v = waifu2x_ex_gui_version();
    int x = waifu2x_ex_gui_upscale_preview("sample_input");
    std::printf("version=%s; preview=%d\n", v, x);
    if(!v || std::strlen(v)==0) return 1;
    return 0;
}
