ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed (ar/ranlib and find)
RUN apt-get update && apt-get install -y --no-install-recommends binutils findutils && rm -rf /var/lib/apt/lists/*

# Build static libraries with the provided Makefile
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc
# Avoid treating warnings as errors to make builds robust under different compilers
ENV WNOERROR=1
RUN make -j$(nproc)

# Install headers (strip leading 'src/') and static libraries to /fuzz/install
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
    && /bin/sh -c 'for f in $(find src -type f -name "*.h"); do rel=${f#src/}; d=/fuzz/install/include/$(dirname "$rel"); mkdir -p "$d"; cp "$f" "$d"/; done' \
    && cp build/*.a /fuzz/install/lib/

# Build and install external dependency objects needed at link time
RUN gf_libafl_cc -DWITH_STDLIB -c src/external_deps/rand.c -o /fuzz/install/lib/rand.o
