ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    cmake \
    ninja-build \
    make \
    libssl-dev \
    libmbedtls-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and build picotls statically
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install
RUN cmake --build /fuzz/build -- -j$(nproc)

# Manual install (project has no install target)
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/picotls && \
    cp -a /fuzz/src/include/*.h /fuzz/install/include/ && \
    cp -a /fuzz/src/include/picotls/*.h /fuzz/install/include/picotls/ && \
    find /fuzz/build -maxdepth 1 -type f -name "lib*.a" -exec cp {} /fuzz/install/lib/ \;
