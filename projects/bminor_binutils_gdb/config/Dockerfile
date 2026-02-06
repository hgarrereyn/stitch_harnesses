ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

# Build and install only libiberty as a static library
WORKDIR /fuzz/src/libiberty
RUN ./configure \
      --prefix=${PREFIX} \
      --enable-install-libiberty \
    && make -j$(nproc) \
    && make install

# Ensure the library and headers are in expected locations
RUN test -f /fuzz/install/lib/libiberty.a && \
    test -d /fuzz/install/include/libiberty
