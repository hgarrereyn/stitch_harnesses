#include <cstdio>
#include <ggml.h>

int main() {
    ggml_init_params params = {};
    params.mem_size = 2 * 1024 * 1024;
    params.mem_buffer = NULL;

    ggml_context* ctx = ggml_init(params);
    if (!ctx) {
        printf("failed to init ggml context\n");
        return 1;
    }

    ggml_tensor* t = ggml_new_tensor_1d(ctx, GGML_TYPE_F32, 1);
    float* data = ggml_get_data_f32(t);
    if (!data) {
        printf("no data pointer\n");
        return 1;
    }
    data[0] = 42.0f;
    printf("tensor[0] = %f\n", data[0]);

    ggml_free(ctx);
    return 0;
}
