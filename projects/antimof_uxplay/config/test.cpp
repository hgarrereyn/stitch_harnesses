#include <cstdio>
extern "C" {
#include <logger.h>
}

static void my_log_cb(void* cls, int level, const char* msg) {
    (void)cls; (void)level;
    std::puts(msg);
}

int main() {
    logger_t* lg = logger_init();
    if (!lg) return 1;
    logger_set_level(lg, LOGGER_DEBUG);
    logger_set_callback(lg, my_log_cb, nullptr);
    logger_log(lg, LOGGER_INFO, "%s %d", "UxPlay logger test", 123);
    logger_destroy(lg);
    return 0;
}
