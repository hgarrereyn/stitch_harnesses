ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and GMP
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config m4 \
    libgmp-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate build system (git checkout requires bootstrap)
RUN ./\.bootstrap || true

# Configure for static build with fuzzing compilers and install prefix
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./configure --disable-shared --enable-static --disable-assembler --disable-fat --prefix=/fuzz/install

# Build and install
RUN make -j"$(nproc)" && make install
