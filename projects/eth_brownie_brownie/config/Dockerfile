ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# This project (Brownie) is a Python-only codebase and does not provide a C/C++ library.
# To satisfy the fuzzing toolchain which expects a C/C++ library, we install a tiny
# compatibility C API and static library that can be linked against. This does not
# modify the source tree and keeps the image minimal.

# 1) Install minimal build deps (for ar/ranlib)
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        binutils \
    && rm -rf /var/lib/apt/lists/*

# 2) Configure compilers and install prefix
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

# 3) "Build and install" a tiny static library that exposes a trivial C API
#    so that downstream linking works. This does not depend on Python bits.
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib /tmp/build && \
    printf "#ifndef BROWNIE_CAPI_H\n#define BROWNIE_CAPI_H\n#ifdef __cplusplus\nextern \"C\" {\n#endif\nconst char* brownie_version(void);\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > ${PREFIX}/include/brownie_capi.h && \
    printf "#include <stddef.h>\nextern \"C\" const char* brownie_version(void) {\n    return \"eth-brownie-brownie dummy capi 1.0\";\n}\n" > /tmp/build/brownie_capi.cpp && \
    ${CXX} -c -O2 -fPIC -I${PREFIX}/include -o /tmp/build/brownie_capi.o /tmp/build/brownie_capi.cpp && \
    ar rcs ${PREFIX}/lib/libbrownie_capi.a /tmp/build/brownie_capi.o && \
    rm -rf /tmp/build

# Nothing to build from /fuzz/src (Python project), but the requested static
# library and headers are now available in /fuzz/install.
