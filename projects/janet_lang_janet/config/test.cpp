#include <stdio.h>
#include <janet/janet.h>

int main() {
    if (janet_init() != 0) {
        fprintf(stderr, "janet_init failed\n");
        return 1;
    }

    JanetTable *env = janet_core_env(NULL);
    Janet out;
    int rc = janet_dostring(env, "(+ 1 2 3)", "test", &out);
    if (rc != 0) {
        fprintf(stderr, "janet_dostring error: %d\n", rc);
        janet_deinit();
        return 1;
    }

    JanetString s = janet_to_string(out);
    printf("Result: %s\n", (const char*)s);

    janet_deinit();
    return 0;
}
