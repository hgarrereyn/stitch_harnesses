#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "puffernet_api.h"

int main() {
    Arena* arena = make_allocator(1024);
    if (!arena) { printf("alloc fail\n"); return 1; }
    float* in = (float*)alloc(arena, 4 * sizeof(float));
    float* out = (float*)alloc(arena, 4 * sizeof(float));
    for (int i = 0; i < 4; i++) in[i] = (i-2);
    _relu(in, out, 4);
    // relu([-2,-1,0,1]) -> [0,0,0,1]
    if (!(out[0]==0 && out[1]==0 && out[2]==0 && out[3]==1)) {
        printf("relu wrong: %f %f %f %f\n", out[0], out[1], out[2], out[3]);
        return 1;
    }
    float s = _sigmoid(0.0f);
    if (s <= 0.49f || s >= 0.51f) { printf("sigmoid wrong %f\n", s); return 1; }
    printf("ok\n");
    return 0;
}
