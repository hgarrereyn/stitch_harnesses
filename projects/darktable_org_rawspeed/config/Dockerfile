ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    libc++-17-dev \
    libc++abi-17-dev \
    libpugixml-dev \
    zlib1g-dev \
    libjpeg-turbo8-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure and build rawspeed
WORKDIR /fuzz/build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_TESTING=OFF \
    -DBUILD_TOOLS=OFF \
    -DBUILD_BENCHMARKING=OFF \
    -DBUILD_FUZZERS=OFF \
    -DWITH_OPENMP=OFF \
    -DRAWSPEED_USE_LIBCXX=ON \
    /fuzz/src
RUN cmake --build . -j

# Manually install: library and headers
RUN set -eux; \
    mkdir -p /fuzz/install/lib /fuzz/install/include/rawspeed; \
    LIBPATH=$(find /fuzz/build -name 'librawspeed.a' | head -n1); \
    cp "$LIBPATH" /fuzz/install/lib/; \
    cp -r /fuzz/src/src/librawspeed/* /fuzz/install/include/rawspeed/; \
    cp /fuzz/build/src/rawspeedconfig.h /fuzz/install/include/rawspeedconfig.h || true; \
    cp /fuzz/src/src/external/ThreadSafetyAnalysis.h /fuzz/install/include/; \
    cp /fuzz/src/src/external/AddressSanitizer.h /fuzz/install/include/; \
    cp /fuzz/src/src/external/MemorySanitizer.h /fuzz/install/include/; \
    :
