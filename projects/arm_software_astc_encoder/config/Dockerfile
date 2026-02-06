ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build static library only (no CLI, no shared libs), scalar ISA for portability
RUN cmake -S /fuzz/src -B /work/build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DASTCENC_CLI=OFF \
    -DASTCENC_SHAREDLIB=OFF \
    -DASTCENC_ISA_NONE=ON \
    -DASTCENC_WERROR=OFF

RUN cmake --build /work/build --target astcenc-none-static -j"$(nproc)"

# Manually install library and public header
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp /work/build/Source/libastcenc-none-static.a /fuzz/install/lib/ \
 && cp /fuzz/src/Source/astcenc.h /fuzz/install/include/
