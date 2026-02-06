ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      ca-certificates build-essential && \
    rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

# Create install dirs
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/benc /fuzz/install/include/memory /fuzz/install/include/util

# Provide a minimal C-only allocator implementation compatible with memory/Allocator.h
# This avoids pulling in the Rust FFI dependency for Allocator.c
RUN printf '%s\n' \
"#include <stdlib.h>" \
"#include <string.h>" \
"#include \"memory/Allocator.h\"" \
"struct Allocator { int dummy; };" \
"struct Allocator* Allocator__new(unsigned long sizeLimit, const char* f, int l){ (void)sizeLimit; (void)f; (void)l; return (struct Allocator*)malloc(sizeof(struct Allocator)); }" \
"void Allocator__free(struct Allocator* a, const char* f, int l){ (void)f; (void)l; free(a); }" \
"int Allocator_isFreeing(Allocator_t* a){ (void)a; return 0; }" \
"void* Allocator__malloc(struct Allocator* a, unsigned long n, const char* f, int l){ (void)a; (void)f; (void)l; return malloc(n); }" \
"void* Allocator__calloc(struct Allocator* a, unsigned long n, unsigned long c, const char* f, int l){ (void)a; (void)f; (void)l; return calloc(c, n); }" \
"void* Allocator__realloc(struct Allocator* a, const void* o, unsigned long n, const char* f, int l){ (void)a; (void)f; (void)l; return realloc((void*)o, n); }" \
"void* Allocator__clone(struct Allocator* a, const void* p, unsigned long n, const char* f, int l){ (void)f; (void)l; void* m = Allocator__malloc(a, n, f, l); if (p && m) { memcpy(m, p, n); } return m; }" \
"struct Allocator* Allocator__child(struct Allocator* a, const char* f, int l){ (void)a; return Allocator__new(0, f, l); }" \
"struct Allocator_OnFreeJob* Allocator__onFree(struct Allocator* a, Allocator_OnFreeCallback cb, void* ctx, const char* f, int l){ (void)a; (void)cb; (void)ctx; (void)f; (void)l; return NULL; }" \
"int Allocator_cancelOnFree(struct Allocator_OnFreeJob* j){ (void)j; return 0; }" \
"void Allocator__adopt(struct Allocator* p, struct Allocator* c, const char* f, int l){ (void)p; (void)c; (void)f; (void)l; }" \
"void Allocator_setCanary(struct Allocator* a, uintptr_t v){ (void)a; (void)v; }" \
"unsigned long Allocator_bytesAllocated(struct Allocator* a){ (void)a; return 0; }" \
"void Allocator_snapshot(struct Allocator* a, int inc){ (void)a; (void)inc; }" \
> /tmp/fuzz_alloc_stub.c

# Provide a minimal Assert_failure implementation to avoid Rust dependency in util/Assert.c
RUN printf '%s\n' \
"#include <stdio.h>" \
"#include <stdlib.h>" \
"#include <stdarg.h>" \
"#include \"util/Assert.h\"" \
"void Assert_failure(const char* format, ...) {" \
"    va_list args;" \
"    va_start(args, format);" \
"    vfprintf(stderr, format, args);" \
"    va_end(args);" \
"    abort();" \
"}" \
> /tmp/fuzz_assert_stub.c

# Build a minimal static C library for the benc utilities and the stubs
WORKDIR /fuzz/src
RUN ${CC} -D__INTELLISENSE__ -I/fuzz/src -c \
      benc/Dict.c \
      benc/List.c \
      benc/String.c \
      util/CString.c \
      util/Bits.c \
      /tmp/fuzz_alloc_stub.c \
      /tmp/fuzz_assert_stub.c && \
    ar rcs /fuzz/install/lib/libbenc.a Dict.o List.o String.o CString.o Bits.o fuzz_alloc_stub.o fuzz_assert_stub.o && \
    rm -f Dict.o List.o String.o CString.o Bits.o fuzz_alloc_stub.o fuzz_assert_stub.o

# Install headers (public API and their deps)
RUN cp -v benc/*.h /fuzz/install/include/benc/ && \
    cp -v memory/Allocator.h /fuzz/install/include/memory/ && \
    cp -v util/*.h /fuzz/install/include/util/
