#include <cstdio>
#include <cstdlib>
#include <cstring>
extern "C" {
#include <ow-crypt.h>
}

int main() {
    const char *password = "secret";
    const char *prefix = "$2b$"; // bcrypt
    const unsigned long cost = 5; // low cost for quick test

    const char input_seed[] = "ABCDEFGHIJKLMNOPQRST"; // 20 bytes of seed
    char *salt = crypt_gensalt_ra(prefix, cost, input_seed, (int)sizeof(input_seed));
    if (!salt) {
        std::printf("Failed to generate salt\n");
        return 1;
    }

    void *buf = nullptr;
    int bufsize = 0;
    char *hash = crypt_ra(password, salt, &buf, &bufsize);
    if (!hash) {
        std::printf("Failed to hash password\n");
        free(salt);
        return 1;
    }

    std::printf("salt=%s\n", salt);
    std::printf("hash=%s\n", hash);

    free(salt);
    free(buf);
    return 0;
}
