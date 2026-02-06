ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install basic build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Build a minimal static library exposing the RPC API (does not require CUDA)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib /tmp/build

# Compile rpc.cpp into a static archive
RUN ${CXX} -fPIC -O2 -c /fuzz/src/rpc.cpp -o /tmp/build/rpc.o && \
    ar rcs ${PREFIX}/lib/libscuda_rpc.a /tmp/build/rpc.o && \
    cp /fuzz/src/rpc.h ${PREFIX}/include/
