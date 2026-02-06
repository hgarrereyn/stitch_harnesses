ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Set compilers to LibAFL wrappers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Build a minimal static library from libretro-common that exposes a small, stable API
WORKDIR /fuzz/src

# Create install directories
RUN mkdir -p /fuzz/install/lib /fuzz/install/include

# Compile a safe, dependency-light component and archive it
RUN mkdir -p build && \
    "$CC" -O2 -fPIC -Ilibretro-common/include -c libretro-common/audio/audio_mix.c -o build/audio_mix.o && \
    "$CC" -O2 -fPIC -Ilibretro-common/include -c libretro-common/memmap/memalign.c -o build/memalign.o && \
    ar rcs /fuzz/install/lib/libretrocommon.a build/audio_mix.o build/memalign.o

# Install headers (public API)
RUN cp -r libretro-common/include/* /fuzz/install/include/
