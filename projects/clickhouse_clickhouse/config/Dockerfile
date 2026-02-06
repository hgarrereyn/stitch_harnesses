ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build header-only pcg-random and install headers into /fuzz/install
RUN apt-get update && apt-get install -y --no-install-recommends cmake ninja-build && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz/src
# Configure (no build artifacts, interface-only)
RUN cmake -S base/pcg-random -B build-pcg \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install

# Install headers manually
RUN mkdir -p /fuzz/install/include \
    && cp -a base/pcg-random/pcg_*.hpp /fuzz/install/include/
