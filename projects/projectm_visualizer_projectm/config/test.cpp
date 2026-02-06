#include <iostream>
#include <projectM-4/projectM.h>

int main() {
    int maj=0, min=0, pat=0;
    projectm_get_version_components(&maj, &min, &pat);
    char* ver = projectm_get_version_string();
    if (ver) {
        std::cout << "libprojectM version: " << ver << " (" << maj << "." << min << "." << pat << ")\n";
    } else {
        std::cout << "libprojectM version components: " << maj << "." << min << "." << pat << "\n";
    }
    // Note: We avoid projectm_create() here because it requires a valid OpenGL context.
    return 0;
}
