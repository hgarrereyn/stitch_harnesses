#include <cstdio>
extern "C" {
#include "raylib.h"
}
#include "raymath.h"

int main() {
    Vector2 a{3.0f, 4.0f};
    Vector2 b{1.0f, 2.0f};
    Vector2 c = Vector2Add(a, b);
    float len = Vector2Length(c);
    std::printf("c=(%0.2f,%0.2f) len=%0.2f\n", c.x, c.y, len);
    return 0;
}
