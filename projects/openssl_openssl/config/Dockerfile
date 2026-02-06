ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for OpenSSL
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    perl \
    libtext-template-perl \
    ca-certificates \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Build and install OpenSSL statically using the fuzzing compilers
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure: build static only, disable tests and zlib to avoid extra deps
RUN ./Configure linux-x86_64 \
      --prefix=/fuzz/install \
      --libdir=lib \
      no-shared \
      no-tests \
      no-zlib \
    && make -j"$(nproc)" \
    && make install_sw
