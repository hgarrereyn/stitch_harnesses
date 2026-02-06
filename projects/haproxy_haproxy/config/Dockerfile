ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Build HAProxy (binary) with fuzzing compilers, minimal features
WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc
ENV LD=stitch_libafl_cc
# Build a generic linux target with minimal options to avoid external deps
RUN make -j$(nproc) TARGET=linux-glibc USE_PCRE2= USE_OPENSSL= USE_ZLIB=

# "Install" into /fuzz/install (binary and docs via Makefile), and also install headers
RUN make install PREFIX=/fuzz/install

# Provide headers to consumers (copy project's headers)
RUN mkdir -p /fuzz/install/include && \
    cp -r include/haproxy /fuzz/install/include/ && \
    cp -r include/import /fuzz/install/include/

# Provide a dummy static library to link against
RUN mkdir -p /fuzz/install/lib && \
    echo 'void __haproxy_dummy(void){}' > /tmp/dummy.c && \
    stitch_libafl_cc -c -o /tmp/dummy.o /tmp/dummy.c && \
    ar rcs /fuzz/install/lib/libhaproxy.a /tmp/dummy.o && \
    rm -f /tmp/dummy.c /tmp/dummy.o
