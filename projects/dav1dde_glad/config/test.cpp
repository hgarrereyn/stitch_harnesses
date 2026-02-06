#include <glad/gl.h>
#include <stdio.h>

int main() {
    // Just reference a GL enum to ensure headers are usable
    printf("GL_VENDOR enum value: 0x%X\n", GL_VENDOR);
    // Reference a glad-defined function pointer type to ensure the API is visible
    PFNGLCLEARPROC fnptr = NULL; (void)fnptr;
    return 0;
}
