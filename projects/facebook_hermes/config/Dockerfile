ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and minimal dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make python3 findutils \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure (top-level, but we'll build only the public target)
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DBUILD_SHARED_LIBS=OFF \
    -DHERMES_ENABLE_TOOLS=OFF \
    -DHERMES_ENABLE_TEST_SUITE=OFF \
    -DHERMES_BUILD_APPLE_FRAMEWORK=OFF \
    -DHERMES_BUILD_SHARED_JSI=OFF

# Build only the hermesPublic static library to keep the image small
RUN cmake --build build --target hermesPublic -j$(nproc)

# Manually install headers and the built static library
RUN set -ex \
 && mkdir -p /fuzz/install/include/hermes/Public /fuzz/install/lib \
 && cp public/hermes/Public/*.h /fuzz/install/include/hermes/Public/ \
 && HER_LIB=$(find build -name 'libhermesPublic.a' -print -quit) \
 && cp "$HER_LIB" /fuzz/install/lib/
