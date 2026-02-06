#include <cstdio>
#include <cstdlib>
#include <cstring>
extern "C" {
#include <libjsonnet.h>
}

int main() {
    JsonnetVm *vm = jsonnet_make();
    if (!vm) {
        printf("Failed to create Jsonnet VM\n");
        return 1;
    }
    int error = 0;
    const char *snippet = "1+2"; // Should evaluate to 3
    char *out = jsonnet_evaluate_snippet(vm, "snippet", snippet, &error);
    if (out == nullptr) {
        printf("jsonnet returned null output\n");
        jsonnet_destroy(vm);
        return 1;
    }
    if (error) {
        printf("Jsonnet evaluation error: %s\n", out);
        jsonnet_realloc(vm, out, 0);
        jsonnet_destroy(vm);
        return 1;
    }
    // Print output (should be "3\n")
    printf("Output: %s", out);
    jsonnet_realloc(vm, out, 0);
    jsonnet_destroy(vm);
    return 0;
}
