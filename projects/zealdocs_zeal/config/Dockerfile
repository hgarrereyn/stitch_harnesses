ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Install build and runtime dependencies for Qt5, SQLite3 and libarchive, plus build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    extra-cmake-modules \
    qtbase5-dev \
    qtwebengine5-dev \
    libqt5x11extras5-dev \
    libxcb-keysyms1-dev \
    libarchive-dev \
    libsqlite3-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Configure and build Zeal
# Use stitch_libafl_cc/stitch_libafl_cxx wrappers as compilers
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install
RUN cmake --build /fuzz/build -j

# Install minimal SDK for fuzzing: headers and the Util static library
RUN mkdir -p /fuzz/install/include/zeal/util /fuzz/install/lib && \
    cp /fuzz/src/src/libs/util/*.h /fuzz/install/include/zeal/util/ && \
    cp /fuzz/build/src/libs/util/libUtil.a /fuzz/install/lib/
