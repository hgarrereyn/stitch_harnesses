ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any extra dependencies (none needed for this minimal C library)
# Build and install a static library to /fuzz/install using required compilers
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

RUN mkdir -p ${PREFIX}/lib ${PREFIX}/include

# Build static library from source in /fuzz/src
WORKDIR /fuzz/src
RUN $CC -O2 -fvisibility=hidden -c char_lib.c -o char_lib.o \
    && ar rcs libchar.a char_lib.o \
    && cp libchar.a ${PREFIX}/lib/ \
    && cp char_lib.h ${PREFIX}/include/
