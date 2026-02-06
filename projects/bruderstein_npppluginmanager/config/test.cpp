#include <stdio.h>
#include <unzip.h>

int main() {
    const char* path = "nonexistent.zip";
    unzFile uf = unzOpen(path);
    if (uf == NULL) {
        printf("Could not open %s (as expected)\n", path);
        return 0;
    } else {
        unzClose(uf);
        printf("Unexpectedly opened %s\n", path);
        return 0;
    }
}
