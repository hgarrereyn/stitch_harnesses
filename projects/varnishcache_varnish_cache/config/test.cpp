#include <iostream>
extern "C" {
#include <vapi/vsm.h>
}

int main() {
    struct vsm *vd = VSM_New();
    if (!vd) {
        std::cout << "VSM_New failed (nullptr)\n";
        return 0;
    }
    const char *err = VSM_Error(vd);
    std::cout << "VSM handle created. Initial error: " << (err ? err : "<none>") << "\n";
    VSM_Destroy(&vd);
    std::cout << "VSM handle destroyed.\n";
    return 0;
}
