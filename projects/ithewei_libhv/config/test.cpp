extern "C" unsigned int gettick_ms();
#include <cstdio>
int main() {
    unsigned int t = gettick_ms();
    std::printf("tick=%u\n", t);
    return 0;
}
