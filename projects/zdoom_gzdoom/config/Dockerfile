ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools and dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config ca-certificates libglib2.0-dev && \
    rm -rf /var/lib/apt/lists/*

# Configure and build ZMusic as a static library
WORKDIR /fuzz/build/zmusic
RUN cmake -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    /fuzz/src/libraries/ZMusic && \
    ninja -j"$(nproc)"

# Manually install headers and static libraries
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp /fuzz/src/libraries/ZMusic/include/zmusic.h /fuzz/install/include/ && \
    cp -v $(find /fuzz/build/zmusic -name 'libzmusic*.a' -type f) /fuzz/install/lib/
