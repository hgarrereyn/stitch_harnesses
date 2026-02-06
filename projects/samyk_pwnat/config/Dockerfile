ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends build-essential && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
ENV PREFIX=/fuzz/install
WORKDIR /fuzz

# Build static library
RUN mkdir -p /fuzz/build && mkdir -p ${PREFIX}/lib ${PREFIX}/include
WORKDIR /fuzz/build

# Compile object files (exclude Windows-only and main program)
RUN ${CC} -O2 -fPIC -I/fuzz/src/src -c \
    /fuzz/src/src/client.c \
    /fuzz/src/src/destination.c \
    /fuzz/src/src/list.c \
    /fuzz/src/src/message.c \
    /fuzz/src/src/packet.c \
    /fuzz/src/src/socket.c \
    /fuzz/src/src/strlcpy.c \
    /fuzz/src/src/udpclient.c \
    /fuzz/src/src/udpserver.c

RUN ar rcs ${PREFIX}/lib/libpwnat.a *.o

# Install headers
RUN cp /fuzz/src/src/common.h ${PREFIX}/include/ && \
    cp /fuzz/src/src/socket.h ${PREFIX}/include/ && \
    cp /fuzz/src/src/message.h ${PREFIX}/include/ && \
    cp /fuzz/src/src/packet.h ${PREFIX}/include/ && \
    cp /fuzz/src/src/list.h ${PREFIX}/include/ && \
    cp /fuzz/src/src/destination.h ${PREFIX}/include/ && \
    cp /fuzz/src/src/client.h ${PREFIX}/include/
