ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any extra dependencies (none required for header-only install)

# Build and install headers to /fuzz/install without requiring submodules
WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN make -f GNUmakefile install prefix=/fuzz/install
