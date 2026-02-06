ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

WORKDIR /tmp/build
# Build static library from the C implementation header
RUN printf '#include <stdlib.h>\n#include "pufferlib/extensions/puffernet.h"\n' > puffernet.c && \
    ${CC} -c -O2 -I/fuzz/src puffernet.c -o puffernet.o && \
    ar rcs libpuffernet.a puffernet.o && \
    mkdir -p ${INSTALL_PREFIX}/lib ${INSTALL_PREFIX}/include && \
    cp libpuffernet.a ${INSTALL_PREFIX}/lib/ && \
    cp /fuzz/src/pufferlib/extensions/puffernet.h ${INSTALL_PREFIX}/include/

# Install a small C API wrapper header with only the declarations needed for linking from C++
RUN cat > ${INSTALL_PREFIX}/include/puffernet_api.h <<'EOF' 
#ifndef PUFFERNET_API_H
#define PUFFERNET_API_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void* data;
    size_t capacity;
    size_t used;
} Arena;

Arena* make_allocator(size_t total_size);
void* alloc(Arena* allocator, size_t size);

void _relu(float* input, float* output, int size);
void _gelu(float* input, float* output, int size);
float _sigmoid(float x);
void _linear(float* input, float* weights, float* bias, float* output,
             int batch_size, int input_dim, int output_dim);
#ifdef __cplusplus
}
#endif
#endif
EOF
