ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools for building a static library
RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Create install directories
RUN mkdir -p /fuzz/install/include /fuzz/install/lib

# Build a tiny compatibility library implementing a subset of the API we can link against without generated data
RUN printf "#include <stdint.h>\nint sizeVarInt(uint32_t value){int size=1;while((value & ~0x7Fu)!=0){value >>= 7; size++;}return size;}\n" > /tmp/varnum_min.c && \
    gf_libafl_cc -O2 -c /tmp/varnum_min.c -o /tmp/varnum_min.o && \
    ar rcs /fuzz/install/lib/libbareiron.a /tmp/varnum_min.o

# Install public headers
RUN cp -r include/* /fuzz/install/include/
