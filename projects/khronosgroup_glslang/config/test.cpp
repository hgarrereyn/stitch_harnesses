#include <cstdio>
#include <glslang/Public/ShaderLang.h>

int main() {
    if (!glslang::InitializeProcess()) {
        printf("InitializeProcess failed\n");
        return 1;
    }
    const char* glslVer = glslang::GetGlslVersionString();
    const char* esslVer = glslang::GetEsslVersionString();
    printf("GLSL: %s\n", glslVer ? glslVer : "(null)");
    printf("ESSL: %s\n", esslVer ? esslVer : "(null)");
    glslang::FinalizeProcess();
    return 0;
}
