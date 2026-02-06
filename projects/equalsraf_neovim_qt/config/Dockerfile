ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (Qt5 dev packages + build tools)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    qtbase5-dev \
    libqt5svg5-dev \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure and build
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz

# Configure
RUN cmake -S /fuzz/src -B /fuzz/build -GNinja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DWITH_QT=Qt5 \
    -DUSE_SYSTEM_MSGPACK=OFF \
    -DENABLE_TESTS=OFF

# Build and (partial) install
RUN cmake --build /fuzz/build --parallel && \
    cmake --install /fuzz/build || true

# Manually install static libraries and headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    find /fuzz/build -type f -name "lib*.a" -exec cp -a {} /fuzz/install/lib/ \; && \
    # Copy entire source include tree to ensure relative includes resolve
    cp -a /fuzz/src/src/* /fuzz/install/include/ && \
    # Install vendored msgpack headers (both source and generated build headers)
    if [ -d /fuzz/build/_deps/msgpack-c-src/include ]; then \
      cp -a /fuzz/build/_deps/msgpack-c-src/include/* /fuzz/install/include/; \
    fi && \
    if [ -d /fuzz/build/_deps/msgpack-c-build/include ]; then \
      cp -a /fuzz/build/_deps/msgpack-c-build/include/* /fuzz/install/include/; \
    fi
