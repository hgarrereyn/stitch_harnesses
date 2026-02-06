ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends build-essential && rm -rf /var/lib/apt/lists/*

# Build a minimal static library from the portable part of the project (hashtable)
RUN mkdir -p /fuzz/install/include /fuzz/install/lib

# Install public header
RUN cp /fuzz/src/src/hashtable.h /fuzz/install/include/

# Compile and archive the static library
RUN CC=stitch_libafl_cc CXX=stitch_libafl_cxx stitch_libafl_cc -std=c99 -O2 -fPIC -include stdint.h -c /fuzz/src/src/hashtable.c -o /tmp/hashtable.o \
 && ar rcs /fuzz/install/lib/libjankyborders.a /tmp/hashtable.o \
 && rm -f /tmp/hashtable.o
