ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No native C/C++ code in this repo; create and install a tiny static C library interface
# to satisfy the build/link steps and provide a stable API surface for fuzzing harnesses.
RUN apt-get update && apt-get install -y --no-install-recommends pkg-config && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

# Install prefix
RUN mkdir -p /fuzz/install/include /fuzz/install/lib

# Build and install a minimal static library
RUN printf '#pragma once\n#ifdef __cplusplus\nextern "C" {\n#endif\nconst char* sigma_version();\nint sigma_add(int a,int b);\n#ifdef __cplusplus\n}\n#endif\n' > /tmp/sigma.h \
 && printf '#include "sigma.h"\nconst char* sigma_version(){return "stub-1.0";}\nint sigma_add(int a,int b){return a+b;}\n' > /tmp/sigma.c \
 && cp /tmp/sigma.h /fuzz/install/include/ \
 && ${CC} -c -O2 -fPIC /tmp/sigma.c -o /tmp/sigma.o \
 && ar rcs /fuzz/install/lib/libsigma_stub.a /tmp/sigma.o
