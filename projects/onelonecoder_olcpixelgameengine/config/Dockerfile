ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal install: header-only library. No external deps needed when using headless mode
# Provide install prefix
ENV PREFIX=/fuzz/install

# Create install dirs and install header
RUN mkdir -p ${PREFIX}/include \
    && cp /fuzz/src/olcPixelGameEngine.h ${PREFIX}/include/

# No build step required (header-only). Ensure compilers are set for downstream builds
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx
