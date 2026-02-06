ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a minimal static library from the vendored zstd in this repo
# This avoids Windows-only sources in the main project and provides a usable C API

# Environment
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p ${INSTALL_PREFIX}/include ${INSTALL_PREFIX}/lib; \
    cd /fuzz/src/Dumper/Utils/Compression; \
    ${CC} -O2 -fPIC -c zstd.c -o zstd.o; \
    ar rcs libdumper7.a zstd.o; \
    ranlib libdumper7.a; \
    cp zstd.h ${INSTALL_PREFIX}/include/; \
    cp libdumper7.a ${INSTALL_PREFIX}/lib/
