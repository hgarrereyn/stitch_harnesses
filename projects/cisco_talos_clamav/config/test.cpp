#include <stdio.h>
#include <clamav.h>

int main() {
    if (cl_init(CL_INIT_DEFAULT) != CL_SUCCESS) {
        printf("cl_init failed\n");
        return 1;
    }
    struct cl_engine* engine = cl_engine_new();
    if (!engine) {
        printf("cl_engine_new failed\n");
        return 1;
    }
    cl_engine_set_num(engine, CL_ENGINE_MAX_FILES, 10);
    int err = 0;
    long long val = cl_engine_get_num(engine, CL_ENGINE_MAX_FILES, &err);
    printf("Engine max files: %lld (err=%d)\n", val, err);

    cl_engine_free(engine);
    printf("OK\n");
    return 0;
}
