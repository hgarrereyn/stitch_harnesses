ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra packages required; compilers are provided by the base image.

# Prepare install dirs
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/SPlisHSPlasH

# Build a minimal static library from core sources that have no external deps
# This avoids fetching heavy external dependencies while still providing a usable API
RUN stitch_libafl_cxx -std=c++17 -O2 -I/fuzz/src -I/fuzz/src/SPlisHSPlasH -I/fuzz/src/extern/eigen \
    -c /fuzz/src/SPlisHSPlasH/SPHKernels.cpp -o /tmp/SPHKernels.o && \
    ar rcs /fuzz/install/lib/libSPlisHSPlasH.a /tmp/SPHKernels.o && \
    rm -f /tmp/SPHKernels.o

# Install the minimal public headers used by our test and harnesses
RUN cp /fuzz/src/SPlisHSPlasH/Common.h /fuzz/install/include/SPlisHSPlasH/ && \
    cp /fuzz/src/SPlisHSPlasH/SPHKernels.h /fuzz/install/include/SPlisHSPlasH/
