ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies to build the C library (libpng and zlib for rwpng.c)
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      libpng-dev zlib1g-dev make pkg-config binutils && \
    rm -rf /var/lib/apt/lists/*

# Build a minimal static library from rwpng.c and install headers
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install
WORKDIR /fuzz/src

RUN mkdir -p ${PREFIX}/lib ${PREFIX}/include && \
    "$CC" -O2 -fPIC -I/fuzz/src -c rwpng.c -o rwpng.o && \
    ar rcs libpngquant_rwpng.a rwpng.o && \
    mv libpngquant_rwpng.a ${PREFIX}/lib/ && \
    install -m 0644 rwpng.h ${PREFIX}/include/
