#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mnr.h>

int main() {
    mnr_print();
    const char* repo = mnr_repo();
    if (!repo) return 1;
    std::printf("Repo URL length: %zu\n", std::strlen(repo));
    return 0;
}
