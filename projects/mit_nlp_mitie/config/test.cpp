#include <cstdio>
#include <cstdlib>
#include <mitie.h>

int main() {
    const char* text = "Bob Smith went to Paris.";
    char** tokens = mitie_tokenize(text);
    if (!tokens) {
        std::printf("tokenize failed\n");
        return 1;
    }
    size_t count = 0;
    for (char** t = tokens; *t; ++t) {
        ++count;
    }
    std::printf("Token count: %zu\n", count);
    mitie_free(tokens);
    return 0;
}
