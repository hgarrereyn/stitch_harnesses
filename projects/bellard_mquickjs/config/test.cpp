#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
extern "C" {
#include "mquickjs.h"
// Declare the stdlib provided by the library archive (C linkage)
extern const JSSTDLibraryDef js_stdlib;
}

int main() {
    const size_t mem_size = 64 * 1024;
    uint8_t *mem_buf = (uint8_t*)malloc(mem_size);
    if (!mem_buf) return 1;

    JSContext *ctx = JS_NewContext(mem_buf, mem_size, &js_stdlib);
    if (!ctx) {
        free(mem_buf);
        return 1;
    }

    const char *src = "1+2";
    JSValue val = JS_Eval(ctx, src, 3, "test", 0);
    if (JS_IsException(val)) {
        JSValue obj = JS_GetException(ctx);
        JS_PrintValueF(ctx, obj, 0);
        printf("\n");
        JS_FreeContext(ctx);
        free(mem_buf);
        return 1;
    }
    JS_PrintValueF(ctx, val, 0);
    printf("\n");

    JS_FreeContext(ctx);
    free(mem_buf);
    return 0;
}
