ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (no viewer, no wayland/systemd/selinux/nettle/gnutls)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake make pkg-config ninja-build ca-certificates \
    zlib1g-dev libjpeg-turbo8-dev libpixman-1-dev libpam0g-dev \
    libx11-dev libxdamage-dev libxfixes-dev libxrandr-dev libxtst-dev libxrender-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure and build
WORKDIR /fuzz/src

# Configure with fuzzing compilers and disable heavy optional components
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_VIEWER=OFF \
    -DENABLE_WAYLAND=OFF \
    -DENABLE_GNUTLS=OFF \
    -DENABLE_NETTLE=OFF \
    -DENABLE_SELINUX=OFF \
    -DENABLE_SYSTEMD=OFF \
    -DENABLE_PWQUALITY=OFF

RUN cmake --build build -j$(nproc)

# Manually install headers (preserve subdirs) and static libs for core components
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -a common/core common/rdr common/network common/rfb /fuzz/install/include/ \
 && cp -a build/common/core/libcore.a build/common/rdr/librdr.a build/common/network/libnetwork.a build/common/rfb/librfb.a /fuzz/install/lib/
