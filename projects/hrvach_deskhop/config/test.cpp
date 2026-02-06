#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <elf2uf2/elf.h>
#include <boot/uf2.h>

// Prototype of the function implemented in the library (defined in main.cpp of elf2uf2)
int elf2uf2(FILE *in, FILE *out);

int main() {
    const char *in_path = "/tmp/in.elf";
    const char *out_path = "/tmp/out.uf2";

    // Create a tiny dummy input file (invalid ELF) just to exercise the code path
    FILE *in = fopen(in_path, "wb");
    if (!in) return 1;
    const char dummy[16] = {0};
    fwrite(dummy, 1, sizeof(dummy), in);
    fclose(in);

    in = fopen(in_path, "rb");
    FILE *out = fopen(out_path, "wb");
    if (!in || !out) return 2;

    // Call the library function; it should return an error code for invalid ELF, but that's fine for testing linking
    int rc = elf2uf2(in, out);

    fclose(in);
    fclose(out);

    // Print result so we know it ran
    printf("elf2uf2 returned %d\n", rc);
    return 0;
}
