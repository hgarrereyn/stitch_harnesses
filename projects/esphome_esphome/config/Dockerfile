ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a minimal static library from the project's C++ sources
# We use the standalone XXTEA component which has no external dependencies.
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/lib ${PREFIX}/include/esphome/components/xxtea

# Compile and archive static library
WORKDIR /tmp/build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ${CXX} -O2 -fPIC -c /fuzz/src/esphome/components/xxtea/xxtea.cpp -o xxtea.o \
 && ar rcs libesphome_xxtea.a xxtea.o \
 && cp libesphome_xxtea.a ${PREFIX}/lib/ \
 && cp /fuzz/src/esphome/components/xxtea/xxtea.h ${PREFIX}/include/esphome/components/xxtea/xxtea.h

# Nothing else to install