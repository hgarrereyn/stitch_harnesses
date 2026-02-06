#include <stdio.h>
#include <h2o.h>

int main() {
    h2o_mem_pool_t pool;
    h2o_mem_init_pool(&pool);

    const char *u = "https://example.com:8443/hello/world?x=1";
    h2o_url_t url = {};
    if (h2o_url_parse(&pool, u, strlen(u), &url) != 0) {
        printf("parse failed\n");
        h2o_mem_clear_pool(&pool);
        return 1;
    }

    h2o_iovec_t s = h2o_url_stringify(&pool, &url);
    printf("url: %.*s\n", (int)s.len, s.base);
    printf("scheme: %.*s, host: %.*s, port: %u, path: %.*s\n",
           (int)url.scheme->name.len, url.scheme->name.base,
           (int)url.host.len, url.host.base,
           (unsigned)h2o_url_get_port(&url),
           (int)url.path.len, url.path.base);

    h2o_mem_clear_pool(&pool);
    return 0;
}
