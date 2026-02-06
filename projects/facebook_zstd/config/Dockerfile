ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install zstd static library and headers
WORKDIR /fuzz/src/lib

# Use the fuzzing compilers
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

# Install only the static library and headers into /fuzz/install
RUN make -j"$(nproc)" install-static install-includes PREFIX=/fuzz/install LIBDIR=/fuzz/install/lib
