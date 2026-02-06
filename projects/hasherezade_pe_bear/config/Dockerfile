ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required tools and init submodules
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    git \
    ninja-build \
    pkg-config \
    cmake \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
RUN git submodule update --init --recursive

# Build only Capstone as a static library
RUN cmake -S /fuzz/src/capstone -B /fuzz/build/capstone \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCAPSTONE_BUILD_STATIC=ON \
    -DCAPSTONE_BUILD_SHARED=OFF \
    -DCAPSTONE_BUILD_TESTS=OFF \
    -DCAPSTONE_INSTALL=OFF
RUN cmake --build /fuzz/build/capstone -j

# Install headers and library manually
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    if [ -f /fuzz/build/capstone/libcapstone.a ]; then cp /fuzz/build/capstone/libcapstone.a /fuzz/install/lib/; fi && \
    if [ -d /fuzz/src/capstone/include ]; then mkdir -p /fuzz/install/include/capstone && cp -r /fuzz/src/capstone/include/capstone/* /fuzz/install/include/capstone/; fi
