ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library from the project's FEC implementation
# and install headers for downstream use.

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install SRC=/fuzz/src

# Build static library and install headers
RUN mkdir -p ${PREFIX}/lib ${PREFIX}/include \
 && cd ${SRC} \
 && ${CXX} -I. -isystem libev -O2 -c lib/fec.cpp -o fec.o \
 && ${CXX} -I. -isystem libev -O2 -c lib/rs.cpp -o rs.o \
 && ar rcs libudpspeeder.a fec.o rs.o \
 && mv libudpspeeder.a ${PREFIX}/lib/ \
 && cp lib/fec.h lib/rs.h ${PREFIX}/include/
