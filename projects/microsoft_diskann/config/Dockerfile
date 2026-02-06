ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal headers needed to compile public API
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libomp-17-dev \
    libboost-program-options-dev \
    libaio-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Create install prefix and provide headers + a dummy static lib to link against
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -a /fuzz/src/include/* /fuzz/install/include/

# Build a tiny dummy static library named libdiskann.a using the fuzzing compilers
RUN echo "void __diskann_dummy(){}" > /tmp/dummy.c \
 && stitch_libafl_cc -c /tmp/dummy.c -o /tmp/dummy.o \
 && ar rcs /fuzz/install/lib/libdiskann.a /tmp/dummy.o \
 && rm -f /tmp/dummy.c /tmp/dummy.o
