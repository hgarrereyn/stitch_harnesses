ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    qtbase5-dev \
    libqt5svg5-dev \
    libqt5x11extras5-dev \
    libx11-dev \
    pkg-config \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/build

RUN cmake -G Ninja /fuzz/src/Kvantum \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DENABLE_QT5=ON \
    -DWITHOUT_KF=ON

RUN cmake --build . --target kvantum -- -v

RUN cmake --install . || true \
    && mkdir -p /fuzz/install/lib /fuzz/install/include/kvantum \
    && find . -name "libkvantum*.so*" -type f -exec cp -v {} /fuzz/install/lib/ \; \
    && cp -v /fuzz/src/Kvantum/style/qt5/*.h /fuzz/install/include/kvantum/
