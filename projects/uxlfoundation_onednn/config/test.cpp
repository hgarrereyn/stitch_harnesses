#include <oneapi/dnnl/dnnl.h>
#include <cstdio>

int main() {
    const dnnl_version_t* v = dnnl_version();
    if (!v) return 1;
    std::printf("oneDNN version: %d.%d.%d (commit: %s)\n", v->major, v->minor, v->patch, v->hash);

    size_t ncpu = dnnl_engine_get_count(dnnl_engine_kind_t::dnnl_cpu);
    std::printf("CPU engines available: %zu\n", ncpu);

    if (ncpu > 0) {
        dnnl_engine_t eng = nullptr;
        if (dnnl_engine_create(&eng, dnnl_engine_kind_t::dnnl_cpu, 0) != dnnl_success) return 1;
        dnnl_engine_destroy(eng);
    }
    return 0;
}
