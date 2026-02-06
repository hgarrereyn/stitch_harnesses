ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools and system dependencies (to satisfy CMake checks)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    cmake \
    ninja-build \
    make \
    pkg-config \
    libcurl4-openssl-dev \
    libssl-dev \
    zlib1g-dev \
    libev-dev \
    libmicrohttpd-dev \
    libtag1-dev \
    libavcodec-dev \
    libavformat-dev \
    libavutil-dev \
    libswresample-dev \
    libmp3lame-dev \
    libncursesw5-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and build only the musikcore target
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install
RUN cmake --build /fuzz/build --target musikcore -j

# Manually install the core library and public headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/musikcore /fuzz/install/include/musikcube/musikcore/sdk \
 && cp /fuzz/src/bin/libmusikcore.so /fuzz/install/lib/ \
 && cp /fuzz/src/src/musikcore/musikcore_c.h /fuzz/install/include/musikcore/musikcore_c.h \
 && cp /fuzz/src/src/musikcore/sdk/*.h /fuzz/install/include/musikcube/musikcore/sdk/
