ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal deps
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx
ENV PREFIX=/fuzz/install

# Create and install a minimal static library exposing a tiny C API so the fuzzer can link
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib /fuzz/build
WORKDIR /fuzz/build
RUN printf '#ifndef LLMFARM_STUB_H\n#define LLMFARM_STUB_H\n#ifdef __cplusplus\nextern "C" {\n#endif\nint llmfarm_stub_version();\nconst char* llmfarm_stub_hello();\n#ifdef __cplusplus\n}\n#endif\n#endif\n' > llmfarm_stub.h \
 && printf '#include "llmfarm_stub.h"\nconst char* llmfarm_stub_hello(){return "LLMFarm";}\nint llmfarm_stub_version(){return 1;}\n' > llmfarm_stub.cpp \
 && ${CXX} -c -O2 -fPIC llmfarm_stub.cpp -I. \
 && ar rcs libllmfarm_stub.a llmfarm_stub.o \
 && cp llmfarm_stub.h ${PREFIX}/include/ \
 && cp libllmfarm_stub.a ${PREFIX}/lib/

# Source is at /fuzz/src (provided by the framework)
WORKDIR /fuzz/src
