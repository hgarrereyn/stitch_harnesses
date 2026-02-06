#include <GL/glew.h>
#include <cstdio>
int main() {
    const GLubyte* s = glewGetErrorString(GLEW_OK);
    if (s) {
        std::printf("GLEW_OK: %s\n", s);
    }
    std::printf("GLEW static test done\n");
    return 0;
}
