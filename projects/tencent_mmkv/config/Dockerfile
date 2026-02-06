ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (ensure available in base image)
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    make \
 && rm -rf /var/lib/apt/lists/*

# Configure and build the project
WORKDIR /build
RUN cmake -G Ninja \
    -S /fuzz/src/POSIX/src \
    -B /build \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
 && ninja

# Install headers and static library
RUN mkdir -p /fuzz/install/include/MMKV /fuzz/install/lib \
 && cp -a /fuzz/src/Core/include/MMKV/* /fuzz/install/include/MMKV/ \
 && cp /build/Core/libcore.a /fuzz/install/lib/
