ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install basic build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Prepare install prefix and headers (no full build to keep image small/fast)
WORKDIR /fuzz
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp -r /fuzz/src/src/include/*.h /fuzz/install/include/
