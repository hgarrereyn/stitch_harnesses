#include <cstdio>
#include <cstdlib>
#include <cstring>
extern "C" {
#include "quickjs/quickjs.h"
}

int main() {
    JSRuntime *rt = JS_NewRuntime();
    if (!rt) return 1;
    JSContext *ctx = JS_NewContext(rt);
    if (!ctx) { JS_FreeRuntime(rt); return 1; }

    const char *code = "1 + 2";
    JSValue val = JS_Eval(ctx, code, strlen(code), "<input>", JS_EVAL_TYPE_GLOBAL);
    if (JS_IsException(val)) {
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
        return 1;
    }
    int32_t result = 0;
    if (JS_ToInt32(ctx, &result, val) < 0) {
        JS_FreeValue(ctx, val);
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
        return 1;
    }
    // Expect 3
    if (result != 3) {
        JS_FreeValue(ctx, val);
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
        return 1;
    }
    JS_FreeValue(ctx, val);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    return 0;
}
