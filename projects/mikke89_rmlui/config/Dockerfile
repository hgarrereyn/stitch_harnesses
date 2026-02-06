ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    libfreetype6-dev \
    libpng-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure and build RmlUi as static library
WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DRMLUI_SAMPLES=OFF \
    -DBUILD_TESTING=OFF \
    -DRMLUI_LUA_BINDINGS=OFF \
    -DRMLUI_LOTTIE_PLUGIN=OFF \
    -DRMLUI_SVG_PLUGIN=OFF \
    -DRMLUI_PRECOMPILED_HEADERS=OFF
RUN cmake --build build --target install
