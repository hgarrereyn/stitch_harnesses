ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for nsjail and its kafel submodule
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    git pkg-config protobuf-compiler libprotobuf-dev libnl-route-3-dev \
    flex bison autoconf automake libtool binutils \
 && rm -rf /var/lib/apt/lists/*

# Set compilers to libAFL wrappers
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Build kafel static lib and nsjail objects/binary
RUN make -j"$(nproc)" kafel/libkafel.a && \
    make -j"$(nproc)"

# Install headers and create a static library libnsjail.a from objects (excluding nsjail.o which contains main)
RUN mkdir -p /fuzz/install/include /fuzz/install/include/kafel /fuzz/install/lib && \
    cp -a *.h config.pb.h /fuzz/install/include/ && \
    cp -a kafel/include/* /fuzz/install/include/kafel/ && \
    cp -a kafel/libkafel.a /fuzz/install/lib/ && \
    ar rcs /fuzz/install/lib/libnsjail.a $(ls *.o | sed 's/^nsjail.o$//' | tr '\n' ' ') && \
    true
