ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any extra dependencies (none required for header-only install)

# Build and install headers to /fuzz/install without requiring submodules
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN make -f GNUmakefile install prefix=/fuzz/install
