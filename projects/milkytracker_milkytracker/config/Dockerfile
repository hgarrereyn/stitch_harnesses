ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (SDL2 + CMake)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    libsdl2-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure and build only the static milkyplay library
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Configure
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install

# Build only the milkyplay target
RUN cmake --build /fuzz/build --target milkyplay -j

# Install: manually copy the static library and public headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/milkyplay \
 && cp /fuzz/build/src/milkyplay/libmilkyplay.a /fuzz/install/lib/ \
 && cp /fuzz/src/src/milkyplay/*.h /fuzz/install/include/milkyplay/
