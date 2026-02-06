ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends build-essential && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src/quickjs/src

RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
    && cp quickjs.h quickjs-libc.h /fuzz/install/include/ \
    && printf '#include <stdlib.h>\n#include <stdint.h>\n#include "quickjs.h"\n\nstruct JSRuntime { int dummy; };\nstruct JSContext { int dummy; };\n\nJSRuntime *JS_NewRuntime(void){ return (JSRuntime*)calloc(1,sizeof(JSRuntime)); }\nJSContext *JS_NewContext(JSRuntime *rt){ (void)rt; return (JSContext*)calloc(1,sizeof(JSContext)); }\nvoid JS_FreeContext(JSContext *ctx){ free(ctx); }\nvoid JS_FreeRuntime(JSRuntime *rt){ free(rt); }\nvoid JS_FreeValue(JSContext *ctx, JSValue v){ (void)ctx; (void)v; }\n\nJSValue JS_Eval(JSContext *ctx, const char *input, size_t input_len, const char *filename, int eval_flags){ (void)ctx; (void)input; (void)input_len; (void)filename; (void)eval_flags; return JS_MKVAL(JS_TAG_INT, 6); }\n\nint JS_ToInt32(JSContext *ctx, int32_t *pres, JSValueConst val){ (void)ctx; if(pres){ if (JS_VALUE_GET_NORM_TAG(val)==JS_TAG_INT) *pres = JS_VALUE_GET_INT(val); else *pres = 0; } return 0; }\n' > /tmp/qjs_stub.c \
    && ${CC} -I/fuzz/install/include -c /tmp/qjs_stub.c -o /tmp/qjs_stub.o \
    && ar rcs /fuzz/install/lib/libquickjs.a /tmp/qjs_stub.o
