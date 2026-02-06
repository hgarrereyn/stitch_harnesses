#include <stdio.h>
#include <string.h>
#include <quickjs.h>

int main() {
    JSRuntime *rt = JS_NewRuntime();
    if (!rt) { printf("Failed to create runtime\n"); return 1; }
    JSContext *ctx = JS_NewContext(rt);
    if (!ctx) { printf("Failed to create context\n"); JS_FreeRuntime(rt); return 1; }

    const char *script = "1 + 2";
    JSValue val = JS_Eval(ctx, script, strlen(script), "<input>", JS_EVAL_TYPE_GLOBAL);
    if (JS_IsException(val)) {
        printf("Eval exception\n");
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
        return 1;
    }
    int32_t result = 0;
    JS_ToInt32(ctx, &result, val);
    JS_FreeValue(ctx, val);

    printf("QuickJS eval result: %d\n", result);

    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    return 0;
}
