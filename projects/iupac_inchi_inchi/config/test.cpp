#include <cstdio>
#include <cstring>
extern "C" {
#include <inchi_api.h>
}

int main() {
    const char *std_inchi = "InChI=1S/H2O/h1H2"; // water
    char key[28] = {0};
    int rc = GetStdINCHIKeyFromStdINCHI(std_inchi, key);
    if (rc != 0) {
        std::printf("Failed to compute InChIKey, rc=%d\n", rc);
        return 1;
    }
    int ok = CheckINCHI(std_inchi, 0);
    std::printf("InChI: %s\nKey: %s\nCheck: %d\n", std_inchi, key, ok);
    return 0;
}
