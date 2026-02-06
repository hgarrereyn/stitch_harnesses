ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies required by njs build (PCRE2 for regex)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libpcre2-dev \
 && rm -rf /var/lib/apt/lists/*

# Build njs static library and "install" headers and libs into /fuzz/install
WORKDIR /fuzz/src

# Use provided compiler wrappers and build only the static library
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Configure and build (disable optional deps to avoid external link requirements)
RUN ./configure --build-dir=build --no-openssl --no-libxml2 --no-zlib && \
    make -j"$(nproc)" libnjs && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp build/libnjs.a /fuzz/install/lib/ && \
    cp build/njs_auto_config.h /fuzz/install/include/ && \
    cp src/*.h /fuzz/install/include/
