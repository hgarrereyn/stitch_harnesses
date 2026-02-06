#include <cstdio>
#include <cstring>
#include <string>
#include <jessibuca.h>

int main() {
    const char* v = jess_version();
    int check = jess_self_check();
    std::string sv = v ? v : "";
    printf("jessibuca version: %s\n", sv.c_str());
    printf("self check: %d\n", check);
    if (sv.size() < 3 || check != 42) return 1;
    return 0;
}
