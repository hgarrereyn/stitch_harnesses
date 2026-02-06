ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    pkg-config \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Build only the C client library and install manually
WORKDIR /fuzz/build/libsphinxclient
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Configure and build the static library
RUN cmake -G Ninja /fuzz/src/api/libsphinxclient \
    -DBUILD_TESTING=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
 && ninja

# Install headers and static lib
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp /fuzz/build/libsphinxclient/libsphinxclient.a /fuzz/install/lib/ \
 && cp /fuzz/src/api/libsphinxclient/sphinxclient.h /fuzz/install/include/
