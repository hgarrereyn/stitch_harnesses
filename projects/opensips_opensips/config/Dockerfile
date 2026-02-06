ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed to build a static lib (ar)
RUN apt-get update && apt-get install -y --no-install-recommends binutils ca-certificates && rm -rf /var/lib/apt/lists/*

# Build a small static crypto library from OpenSIPS hashing sources and install headers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install
WORKDIR /fuzz/src

# Create install dirs
RUN mkdir -p ${PREFIX}/include/opensips ${PREFIX}/lib

# Compile sources into objects using the fuzzing compiler wrappers
RUN $CC -O2 -fPIC -c md5.c sha1.c sha256.c sha512.c

# Archive into a static library
RUN ar rcs ${PREFIX}/lib/libopensipscrypto.a md5.o sha1.o sha256.o sha512.o && rm -f md5.o sha1.o sha256.o sha512.o

# Install public headers used by this library
RUN cp md5.h md5global.h sha1.h sha256.h sha512.h ${PREFIX}/include/opensips/
