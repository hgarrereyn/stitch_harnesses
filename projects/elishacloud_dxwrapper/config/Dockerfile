ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tooling
RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

# Build a tiny static library to link against (project is Windows-specific; provide a portable shim)
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN mkdir -p /build && mkdir -p /fuzz/install/include && mkdir -p /fuzz/install/lib \
 && printf "#include <stdint.h>\nint dxw_hello(void){return 42;}\n" > /build/dummy.c \
 && printf "#ifndef DXWRAPPER_SHIM_H\n#define DXWRAPPER_SHIM_H\n#ifdef __cplusplus\nextern \"C\" {\n#endif\nint dxw_hello(void);\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > /fuzz/install/include/dxwrapper.h \
 && ${CC} -fPIC -O2 -c /build/dummy.c -o /build/dummy.o \
 && ar rcs /fuzz/install/lib/libdxwrapper.a /build/dummy.o

# Nothing else to install; headers and lib are in /fuzz/install
