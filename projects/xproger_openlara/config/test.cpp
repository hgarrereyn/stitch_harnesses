#include <cstdio>
#include <openlara/utils.h>

int main() {
    vec3 a(1.0f, 2.0f, 3.0f);
    vec3 b(4.0f, 5.0f, 6.0f);
    vec3 c = a + b;
    std::printf("sum: %.1f %.1f %.1f\n", c.x, c.y, c.z);
    return 0;
}
