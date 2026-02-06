ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools (gcc for host tools, make for building)
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Build the project objects using the fuzzing compilers and generate stdlib headers with host gcc
RUN make -j"$(nproc)" CC=stitch_libafl_cc HOST_CC=gcc

# Build an object that embeds the generated standard library definition (C-only),
# providing minimal stubs for helper functions required by mqjs_stdlib.h
RUN printf '%s\n' \
  '#include <stddef.h>' \
  '#include "mquickjs.h"' \
  'static JSValue js_print(JSContext *ctx, JSValue *this_val, int argc, JSValue *argv) { (void)ctx; (void)this_val; (void)argc; (void)argv; return JS_UNDEFINED; }' \
  'static JSValue js_gc(JSContext *ctx, JSValue *this_val, int argc, JSValue *argv) { (void)ctx; (void)this_val; (void)argc; (void)argv; return JS_UNDEFINED; }' \
  'static JSValue js_load(JSContext *ctx, JSValue *this_val, int argc, JSValue *argv) { (void)ctx; (void)this_val; (void)argc; (void)argv; return JS_UNDEFINED; }' \
  'static JSValue js_setTimeout(JSContext *ctx, JSValue *this_val, int argc, JSValue *argv) { (void)ctx; (void)this_val; (void)argc; (void)argv; return JS_UNDEFINED; }' \
  'static JSValue js_clearTimeout(JSContext *ctx, JSValue *this_val, int argc, JSValue *argv) { (void)ctx; (void)this_val; (void)argc; (void)argv; return JS_UNDEFINED; }' \
  'static JSValue js_date_now(JSContext *ctx, JSValue *this_val, int argc, JSValue *argv) { (void)this_val; (void)argc; (void)argv; return JS_NewInt64(ctx, 0); }' \
  'static JSValue js_performance_now(JSContext *ctx, JSValue *this_val, int argc, JSValue *argv) { (void)this_val; (void)argc; (void)argv; return JS_NewInt64(ctx, 0); }' \
  '#include "mqjs_stdlib.h"' > gen_stdlib_obj.c \
 && stitch_libafl_cc -c -o mqjs_stdlib.o gen_stdlib_obj.c

# Create a static library from the engine objects (including stdlib object) and install the public header
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && ar rcs /fuzz/install/lib/libmquickjs.a mquickjs.o dtoa.o libm.o cutils.o mqjs_stdlib.o \
 && install -m 0644 mquickjs.h /fuzz/install/include/
