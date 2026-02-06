ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && apt-get install -y --no-install-recommends build-essential cmake ninja-build && rm -rf /var/lib/apt/lists/*

# Build MMKV core as a static library and install headers
RUN cmake -S /fuzz/src/MMKV/Core -B /build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DBUILD_SHARED_LIBS=OFF
RUN cmake --build /build -j"$(nproc)"

# Manual install: copy library and headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp /build/libcore.a /fuzz/install/lib/ && \
    cp -r /fuzz/src/MMKV/Core/*.h /fuzz/install/include/ && \
    cp -r /fuzz/src/MMKV/Core/*.hpp /fuzz/install/include/ || true && \
    mkdir -p /fuzz/install/include/aes/openssl /fuzz/install/include/crc32/zlib && \
    cp -r /fuzz/src/MMKV/Core/aes/*.h /fuzz/install/include/aes/ && \
    cp -r /fuzz/src/MMKV/Core/aes/openssl/* /fuzz/install/include/aes/openssl/ && \
    cp -r /fuzz/src/MMKV/Core/crc32/*.h /fuzz/install/include/crc32/ && \
    cp -r /fuzz/src/MMKV/Core/crc32/zlib/* /fuzz/install/include/crc32/zlib/
