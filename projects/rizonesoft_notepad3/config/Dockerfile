ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install tinyexpr (vendored in Notepad3) as a static library
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/build

# Build static libtinyexpr.a
RUN ${CC} -O2 -c /fuzz/src/src/tinyexpr/tinyexpr.c -o tinyexpr.o \
 && ar rcs libtinyexpr.a tinyexpr.o \
 && mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp libtinyexpr.a /fuzz/install/lib/ \
 && cp /fuzz/src/src/tinyexpr/tinyexpr.h /fuzz/install/include/
