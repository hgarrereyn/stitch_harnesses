#include <cstdio>
extern "C" {
#include <sapi/embed/php_embed.h>
}

int main() {
    int argc = 0; char **argv = nullptr;
    if (php_embed_init(argc, argv) == FAILURE) {
        std::printf("php_embed_init failed\n");
        return 1;
    }

    zend_eval_string_ex(const_cast<char*>("echo 'Hello from embedded PHP\\n';"), nullptr, "embedded", 1);

    php_embed_shutdown();
    return 0;
}
