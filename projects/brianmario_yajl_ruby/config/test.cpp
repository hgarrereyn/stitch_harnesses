#include <cstdio>
#include <cstring>
#include <api/yajl_gen.h>
#include <api/yajl_parse.h>

int main() {
    // Configure and generate a small JSON document
    yajl_gen_config cfg; memset(&cfg, 0, sizeof(cfg)); cfg.beautify = 0; cfg.indentString = NULL; cfg.htmlSafe = 0;
    yajl_gen g = yajl_gen_alloc(&cfg, nullptr);
    if (!g) { fprintf(stderr, "failed to alloc generator\n"); return 1; }
    yajl_gen_map_open(g);
    const unsigned char key1[] = "hello";
    yajl_gen_string(g, key1, (unsigned int)(sizeof("hello")-1));
    const unsigned char val1[] = "world";
    yajl_gen_string(g, val1, (unsigned int)(sizeof("world")-1));
    yajl_gen_map_close(g);

    const unsigned char *buf = nullptr;
    unsigned int len = 0;
    yajl_gen_get_buf(g, &buf, &len);
    printf("Generated JSON (%u bytes): %s\n", len, buf);

    // Touch a parse API symbol to ensure linkage
    const char *ok = yajl_status_to_string(yajl_status_ok);
    printf("Status ok string: %s\n", ok);

    yajl_gen_clear(g);
    yajl_gen_free(g);
    return 0;
}
