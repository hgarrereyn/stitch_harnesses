ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install runtime build dependencies for headers that may include system libs
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    pkg-config \
    libevdev-dev \
    libudev-dev \
    libconfig++-dev \
    libglib2.0-dev \
    binutils \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Manually install headers as the upstream build requires a missing submodule
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cd /fuzz/src/src/logid \
 && find . -type f -name "*.h" -print0 | xargs -0 -I {} sh -c 'mkdir -p /fuzz/install/include/$(dirname {}) && cp {} /fuzz/install/include/{}' \
 && cp ipc_defs.h /fuzz/install/include/ipc_defs.h \
 && cd /fuzz/install/lib \
 && echo "int logiops_dummy = 0;" > dummy.c \
 && $CC -c dummy.c -o dummy.o \
 && ar rcs liblogiops.a dummy.o \
 && rm -f dummy.c dummy.o
