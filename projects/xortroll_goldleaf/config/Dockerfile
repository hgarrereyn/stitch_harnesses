ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install basic build tools (ar, etc.)
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx
ENV PREFIX=/fuzz/install

# Create a minimal static library that exposes a tiny API compatible with host toolchain
# This is necessary because the original project targets Nintendo Switch (devkitA64/libnx)
# and cannot be built with the provided host compilers.
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib /tmp/build && \
    cat > /tmp/build/goldleaf_compat.hpp <<'EOF'
#ifndef GOLDLEAF_COMPAT_HPP
#define GOLDLEAF_COMPAT_HPP
namespace goldleaf_compat {
const char* version();
int add(int a, int b);
}
#endif
EOF
RUN cat > /tmp/build/goldleaf_compat.cpp <<'EOF'
#include "goldleaf_compat.hpp"
namespace goldleaf_compat {
const char* version() { return "goldleaf-compat 0.1"; }
int add(int a, int b) { return a + b; }
}
EOF
RUN ${CXX} -O2 -fPIC -c /tmp/build/goldleaf_compat.cpp -o /tmp/build/goldleaf_compat.o && \
    ar rcs /tmp/build/libgoldleaf_compat.a /tmp/build/goldleaf_compat.o && \
    cp /tmp/build/libgoldleaf_compat.a ${PREFIX}/lib/ && \
    cp /tmp/build/goldleaf_compat.hpp ${PREFIX}/include/

# Nothing else to build/install
