ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    cmake \
    ninja-build \
    make \
    libglib2.0-dev \
    libudev-dev \
    libsystemd-dev \
    libreadline-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DENABLE_SYSTEMD=ON \
    -DBUILD_TESTS=OFF && \
    cmake --build build --target miracle-shared

# Manually install the static library and headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp build/src/shared/libmiracle-shared.a /fuzz/install/lib/ && \
    cp src/shared/*.h /fuzz/install/include/
