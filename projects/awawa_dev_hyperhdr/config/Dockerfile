ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make \
    qtbase5-dev libqt5serialport5-dev libturbojpeg-dev \
    ca-certificates pkg-config \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

# Configure with most features disabled for a lightweight setup
RUN cmake -S . -B /fuzz/build \
    -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DUSE_SHARED_LIBS=OFF \
    -DDO_NOT_USE_QT_VERSION_6_LIBS=ON \
    -DPLATFORM=linux \
    -DENABLE_SPIDEV=OFF \
    -DENABLE_SPI_FTDI=OFF \
    -DENABLE_WS281XPWM=OFF \
    -DENABLE_DX=OFF \
    -DENABLE_FRAMEBUFFER=OFF \
    -DENABLE_AMLOGIC=OFF \
    -DENABLE_MAC_SYSTEM=OFF \
    -DENABLE_PIPEWIRE=OFF \
    -DENABLE_PIPEWIRE_EGL=OFF \
    -DENABLE_X11=OFF \
    -DENABLE_AVF=OFF \
    -DENABLE_MF=OFF \
    -DENABLE_V4L2=OFF \
    -DENABLE_SOUNDCAPLINUX=OFF \
    -DENABLE_SOUNDCAPMACOS=OFF \
    -DENABLE_SOUNDCAPWINDOWS=OFF \
    -DENABLE_CEC=OFF \
    -DENABLE_MQTT=OFF \
    -DENABLE_POWER_MANAGEMENT=OFF \
    -DENABLE_PROTOBUF=OFF \
    -DENABLE_SYSTRAY=OFF \
    -DENABLE_ZSTD=OFF \
    -DUSE_PRECOMPILED_HEADERS=OFF

# Install headers for consumers (library build is heavy and not required for header-only testing)
RUN mkdir -p /fuzz/install/include && cp -r /fuzz/src/include/* /fuzz/install/include/
