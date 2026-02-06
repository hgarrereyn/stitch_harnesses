ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed to create a dummy static lib and install headers
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    file \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Environment
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

# Install headers and create a minimal static library archive to satisfy linking
RUN set -eux; \
    mkdir -p ${PREFIX}/include ${PREFIX}/lib; \
    cp -R /fuzz/src/include/* ${PREFIX}/include/; \
    # Create a tiny object and archive as libbgfx.a so linkers can resolve the library name
    echo 'extern "C" void __bgfx_dummy_symbol(void){}' > /tmp/dummy.cpp; \
    ${CXX} -c -O2 -fPIC /tmp/dummy.cpp -o /tmp/dummy.o; \
    ar rcs ${PREFIX}/lib/libbgfx.a /tmp/dummy.o; \
    ranlib ${PREFIX}/lib/libbgfx.a; \
    rm -f /tmp/dummy.cpp /tmp/dummy.o
