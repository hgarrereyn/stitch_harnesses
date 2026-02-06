ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install basic build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Prepare install prefix
ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib

# Install minimal public header(s)
RUN install -m 0644 -D /fuzz/src/packages/react-native-nitro-modules/cpp/utils/NitroDefines.hpp ${PREFIX}/include/NitroDefines.hpp

# Build a tiny static library to satisfy linker requirements
RUN echo "void __nitro_placeholder(){}" > /tmp/placeholder.c && \
    CC=gf_libafl_cc CXX=gf_libafl_cxx gf_libafl_cc -c /tmp/placeholder.c -o /tmp/placeholder.o && \
    ar rcs ${PREFIX}/lib/libnitro.a /tmp/placeholder.o && \
    rm -f /tmp/placeholder.c /tmp/placeholder.o
