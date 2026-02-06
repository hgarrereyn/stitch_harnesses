ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools (make) and certificates
RUN apt-get update && apt-get install -y --no-install-recommends make ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

# Build and install the massdns binary using Makefile
RUN make -j$(nproc) && make install PREFIX=/fuzz/install

# Install headers and create a minimal static library for linking
RUN mkdir -p /fuzz/install/include/massdns /fuzz/install/lib \
 && cp -v src/*.h /fuzz/install/include/massdns/ \
 && printf "void massdns_dummy(void){}\n" > /tmp/dummy.c \
 && ${CC} -c /tmp/dummy.c -o /tmp/dummy.o \
 && ar rcs /fuzz/install/lib/libmassdns.a /tmp/dummy.o
