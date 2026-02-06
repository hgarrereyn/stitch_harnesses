#include <nuklear.h>
#include <cstdio>

int main() {
    nk_buffer buf; 
    nk_buffer_init_default(&buf);
    nk_buffer_clear(&buf);
    nk_buffer_free(&buf);
    std::printf("Nuklear basic buffer test OK\n");
    return 0;
}
