#include <iostream>
extern "C" {
#include <talloc.h>
}

int main() {
    std::cout << "talloc version: " << talloc_version_major() << "." << talloc_version_minor() << "\n";
    TALLOC_CTX *ctx = (TALLOC_CTX*)talloc_init("root");
    if (!ctx) {
        std::cout << "failed to create ctx\n";
        return 0;
    }
    char *s = (char*)_talloc(ctx, 32);
    if (s) {
        strcpy(s, "hello talloc");
        std::cout << s << "\n";
    }
    talloc_free(ctx);
    return 0;
}
