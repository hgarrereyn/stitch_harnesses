ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    cmake \
    make \
    pkg-config \
    ninja-build \
    libssl-dev \
    zlib1g-dev \
    libsodium-dev \
    protobuf-compiler \
    libprotobuf-dev \
    libunwind-dev \
    libutempter-dev \
    libselinux1-dev \
    libcurl4-openssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure and build (static libs), install to /fuzz/install
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DDISABLE_VCPKG=ON \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTING=OFF \
    -DFUZZING=OFF \
    && cmake --build /fuzz/build --target install -j

# Manually install static libraries and headers for linking
RUN set -eux; \
    mkdir -p /fuzz/install/lib; \
    cp /fuzz/build/libet-lib.a /fuzz/install/lib/ || true; \
    cp /fuzz/build/libTerminalCommon.a /fuzz/install/lib/ || true; \
    cp /fuzz/build/libHtmCommon.a /fuzz/install/lib/ || true; \
    mkdir -p /fuzz/install/include/et; \
    cd /fuzz/src && \
    mkdir -p /fuzz/install/include/et/base /fuzz/install/include/et/terminal/forwarding /fuzz/install/include/et/htm; \
    cp -a src/base/*.hpp /fuzz/install/include/et/base/; \
    cp -a src/terminal/*.hpp /fuzz/install/include/et/terminal/; \
    cp -a src/terminal/forwarding/*.hpp /fuzz/install/include/et/terminal/forwarding/; \
    cp -a src/htm/*.hpp /fuzz/install/include/et/htm/; \
    # Protobuf-generated headers
    cp -a /fuzz/build/ET.pb.h /fuzz/install/include/et/ || true; \
    cp -a /fuzz/build/ETerminal.pb.h /fuzz/install/include/et/ || true
