#include <cstdio>
#include <cstring>
#include <cstdint>
#include <clamav.h>

int main() {
    printf("ClamAV version: %s\n", cl_retver());

    if (cl_init(CL_INIT_DEFAULT) != CL_SUCCESS) {
        printf("cl_init failed\n");
        return 0; // don't fail test
    }

    struct cl_engine *engine = cl_engine_new();
    if (!engine) {
        printf("cl_engine_new failed\n");
        return 0;
    }

    int ret = cl_engine_compile(engine);
    printf("cl_engine_compile ret=%d\n", ret);

    const char *data = "Hello, world";
    const unsigned char *udata = (const unsigned char*)data;

    struct cl_scan_options options = {0};
    options.parse = CL_SCAN_PARSE_ARCHIVE | CL_SCAN_PARSE_ELF | CL_SCAN_PARSE_PDF;
    options.general = CL_SCAN_GENERAL_HEURISTICS;

    cl_fmap_t *map = cl_fmap_open_memory(udata, strlen(data));
    if (map) {
        cl_verdict_t verdict = CL_VERDICT_NOTHING_FOUND;
        const char *last_alert = NULL;
        uint64_t scanned = 0;
        char *hash_out = NULL;
        char *file_type_out = NULL;
        ret = cl_scanmap_ex(map, "mem", &verdict, &last_alert, &scanned, engine, &options,
                             NULL, NULL, &hash_out, NULL, NULL, &file_type_out);
        printf("cl_scanmap_ex ret=%d verdict=%d last_alert=%s scanned=%llu file_type=%s\n",
               ret, verdict, last_alert ? last_alert : "(none)",
               (unsigned long long)scanned,
               file_type_out ? file_type_out : "(none)");
        if (hash_out) free(hash_out);
        if (file_type_out) free(file_type_out);
        cl_fmap_close(map);
    } else {
        printf("cl_fmap_open_memory failed\n");
    }

    cl_engine_free(engine);
    return 0;
}
