ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed to create a static library
RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

# Build a minimal static library from the portable QR code generator component
# The full project is a Windows-only GUI; on Linux we expose the vendored portable
# QR encoder as a static library for fuzzing/consumption.
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install

RUN mkdir -p ${PREFIX}/lib ${PREFIX}/include/qrcodegen && \
    ${CC} -O2 -fPIC -I/fuzz/src/qrcodegen -c /fuzz/src/qrcodegen/qrcodegen.c -o /tmp/qrcodegen.o && \
    ar rcs ${PREFIX}/lib/libqrcodegen.a /tmp/qrcodegen.o && \
    install -m 0644 /fuzz/src/qrcodegen/qrcodegen.h ${PREFIX}/include/qrcodegen/qrcodegen.h
