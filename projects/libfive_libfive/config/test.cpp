#include <cstdio>
#include "libfive.h"

int main() {
    // Simple test: evaluate the X variable at a point
    libfive_tree tx = libfive_tree_x();
    libfive_vec3 p{3.14f, 2.0f, -1.0f};
    float v = libfive_tree_eval_f(tx, p);
    printf("x at point = %f\n", v);
    libfive_tree_delete(tx);
    return (v > 3.0f && v < 3.2f) ? 0 : 1;
}
