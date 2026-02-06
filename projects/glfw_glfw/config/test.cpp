#include <stdio.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) {
        // Likely headless CI without DISPLAY; this is fine for a build test
        printf("glfwInit failed (likely no display).\n");
        return 0;
    }

    // Query a trivial piece of API to ensure symbols resolve
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    printf("GLFW version reported: %d.%d.%d\n", major, minor, rev);

    glfwTerminate();
    return 0;
}
