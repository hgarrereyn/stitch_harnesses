#include <cstdio>
#include <cstdlib>
#include <php.h>
#include "php_yaf.h"

int main() {
    const char* ver = PHP_YAF_VERSION;
    std::printf("Yaf header available, version: %s\n", ver);
    zval zv;
    ZVAL_NULL(&zv);
    if (Z_TYPE(zv) == IS_NULL) {
        std::puts("PHP zval works");
    }
    return 0;
}
