ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal dependencies if needed
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Environment for compilers
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

# "Build and install": for header-only subset we install headers into /fuzz/install/include
RUN mkdir -p ${PREFIX}/include && \
    cp -r /fuzz/src/mediapipe ${PREFIX}/include/

# No libraries are built; headers are sufficient for simple test programs
