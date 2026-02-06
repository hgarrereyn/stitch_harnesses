#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "quickjs.h"
}

int main() {
    JSRuntime *rt = JS_NewRuntime();
    if (!rt) {
        printf("Failed to create runtime\n");
        return 1;
    }
    JSContext *ctx = JS_NewContext(rt);
    if (!ctx) {
        printf("Failed to create context\n");
        JS_FreeRuntime(rt);
        return 1;
    }

    const char *code = "1 + 2 + 3";
    JSValue val = JS_Eval(ctx, code, strlen(code), "test.js", JS_EVAL_TYPE_GLOBAL);
    int32_t res = 0;
    if (JS_IsException(val)) {
        printf("Eval exception\n");
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
        return 1;
    }
    if (JS_ToInt32(ctx, &res, val) == 0) {
        printf("Result: %d\n", res);
    } else {
        printf("Could not convert result to int\n");
    }
    JS_FreeValue(ctx, val);

    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    return 0;
}
