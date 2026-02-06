ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
 && rm -rf /var/lib/apt/lists/*

# Set compilers to the fuzzing wrappers
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Build and install BLIS as a static library
WORKDIR /fuzz/src
RUN ./configure --prefix=/fuzz/install --disable-shared --enable-static --enable-cblas auto \
 && make -j"$(nproc)" \
 && make install
