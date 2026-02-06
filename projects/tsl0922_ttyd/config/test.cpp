#include <cstddef>
#include <cstdio>
#include <cstring>
extern "C" {
#include <ttyd/utils.h>
}

int main() {
    char text[32];
    std::snprintf(text, sizeof(text), "%s", "hello");
    // uppercase in-place
    uppercase(text);

    char sigbuf[32];
    get_sig_name(1, sigbuf, sizeof(sigbuf)); // SIGHUP on most systems

    int sig = get_sig("HUP");

    std::printf("text=%s signame=%s sig=%d\n", text, sigbuf, sig);
    return 0;
}
