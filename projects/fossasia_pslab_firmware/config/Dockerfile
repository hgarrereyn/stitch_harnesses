ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools to create a static library
RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

# Set compilers to the required wrappers
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Create install directories
RUN mkdir -p /fuzz/install/include /fuzz/install/lib

# Install a subset of public headers that are compiler-agnostic
# The firmware itself targets a Microchip MCU and cannot be built with clang.
# For fuzzing/compilation, we expose stable C headers and provide a dummy static lib for linkage.
RUN cp /fuzz/src/src/commands.h /fuzz/install/include/ && \
    cp /fuzz/src/src/states.h /fuzz/install/include/

# Build a tiny static library to satisfy linker requirements
RUN printf "void __pslabfirmware_dummy(void){}" > /tmp/dummy.c && \
    ${CC} -c /tmp/dummy.c -o /tmp/dummy.o && \
    ar rcs /fuzz/install/lib/libpslabfirmware.a /tmp/dummy.o && \
    rm -f /tmp/dummy.c /tmp/dummy.o
