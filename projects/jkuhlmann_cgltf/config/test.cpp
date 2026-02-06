#include <cstdio>
#include <cstring>
extern "C" {
#include "cgltf.h"
}

int main() {
    const char* json = "{\n  \"asset\": { \"version\": \"2.0\" }\n}";
    cgltf_options options = {};
    cgltf_data* data = NULL;
    cgltf_result res = cgltf_parse(&options, json, strlen(json), &data);
    if (res != cgltf_result_success) {
        std::printf("parse failed: %d\n", (int)res);
        return 1;
    }
    cgltf_validate(data);
    cgltf_free(data);
    std::puts("ok");
    return 0;
}
