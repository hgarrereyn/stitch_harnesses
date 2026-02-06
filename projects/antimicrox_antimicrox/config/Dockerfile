ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    pkg-config \
    ninja-build \
    extra-cmake-modules \
    qtbase5-dev \
    qttools5-dev \
    libdbus-1-dev \
    libsdl2-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install antimicrox
WORKDIR /fuzz/build
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN cmake -G Ninja /fuzz/src \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DWITH_X11=OFF \
    -DWITH_XTEST=OFF \
    -DWITH_UINPUT=ON \
    -DAPPDATA=OFF \
    -DUSE_QT6_BY_DEFAULT=OFF
RUN ninja -j"$(nproc)" && ninja install

# Install headers for external use (copy project headers and generated config.h)
RUN mkdir -p /fuzz/install/include && \
    find /fuzz/src/src -type f -name '*.h' -print0 | while IFS= read -r -d '' f; do \
      rel="${f#/fuzz/src/src/}"; \
      mkdir -p "/fuzz/install/include/$(dirname "$rel")"; \
      cp "$f" "/fuzz/install/include/$rel"; \
    done && \
    cp /fuzz/build/config.h /fuzz/install/include/
