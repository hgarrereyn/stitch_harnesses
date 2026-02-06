ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a static library and install headers
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Build static library manually and install headers/lib
RUN mkdir -p /fuzz/build && mkdir -p ${PREFIX}/lib ${PREFIX}/include \
 && ${CXX} -O2 -c tgaimage.cpp -I. -o /fuzz/build/tgaimage.o \
 && ${CXX} -O2 -c geometry.h -x c++ -I. -o /fuzz/build/geometry.o || true \
 && ${CXX} -O2 -c model.cpp -I. -o /fuzz/build/model.o \
 && ${CXX} -O2 -c our_gl.cpp -I. -o /fuzz/build/our_gl.o \
 && ar rcs ${PREFIX}/lib/libtinyrenderer.a /fuzz/build/tgaimage.o /fuzz/build/model.o /fuzz/build/our_gl.o \
 && cp -a tgaimage.h geometry.h model.h our_gl.h ${PREFIX}/include/