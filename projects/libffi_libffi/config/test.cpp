#include <stdio.h>
#include <ffi.h>

static int add_ints(int a, int b) { return a + b; }

int main() {
    ffi_cif cif;
    ffi_type *args[2];
    void *values[2];
    int a = 2, b = 40;
    int result = 0;

    args[0] = &ffi_type_sint;
    args[1] = &ffi_type_sint;
    values[0] = &a;
    values[1] = &b;

    if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 2, &ffi_type_sint, args) != FFI_OK) {
        printf("ffi_prep_cif failed\n");
        return 1;
    }

    ffi_call(&cif, FFI_FN(add_ints), &result, values);
    printf("Result: %d\n", result);
    return result == 42 ? 0 : 1;
}
