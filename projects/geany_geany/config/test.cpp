#include <cstdio>
#include <geany/support.h>

int main() {
    const char* s = _("Hello, Geany!");
    std::printf("%s\n", s);
    return 0;
}
