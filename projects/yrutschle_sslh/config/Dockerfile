ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libpcre2-dev \
    libconfig-dev \
    libev-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure (generate config.h) with our compilers
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Build without generating the man page to avoid perl/pod2man dependency
RUN ./configure && \
    make -j"$(nproc)" MAN= && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    # Install static library produced by the Makefile
    cp -v libsslh.a /fuzz/install/lib/ && \
    # Install headers needed to use the library API
    cp -v argtable3.h collection.h common.h gap.h log.h probe.h processes.h sslh-conf.h tcp-listener.h tcp-probe.h tls.h udp-listener.h proxyprotocol.h config.h version.h /fuzz/install/include/ && \
    # Optionally install the sslh binary (not used for fuzzing, but handy)
    cp -v sslh-fork /fuzz/install/sslh || true
