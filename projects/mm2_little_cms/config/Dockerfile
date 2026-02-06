ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools needed by autotools project
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Set compilers to the provided fuzzing-aware wrappers
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure, build, and install static library
RUN ./configure --prefix=/fuzz/install --enable-static --disable-shared \
 && make -j"$(nproc)" \
 && make install \
 && true
