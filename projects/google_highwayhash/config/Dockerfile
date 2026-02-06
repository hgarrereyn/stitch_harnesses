ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (cmake and ninja)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build static library with fuzzing compilers
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Configure
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF

# Build the library target
RUN cmake --build /fuzz/build --target highwayhash -j$(nproc)

# Manually install: copy static library and headers
RUN set -eux; \
    mkdir -p /fuzz/install/lib /fuzz/install/include; \
    LIB=$(find /fuzz/build -name 'libhighwayhash.a' -print -quit); \
    cp "$LIB" /fuzz/install/lib/; \
    mkdir -p /fuzz/install/include/highwayhash; \
    cp -r /fuzz/src/highwayhash/* /fuzz/install/include/highwayhash/
