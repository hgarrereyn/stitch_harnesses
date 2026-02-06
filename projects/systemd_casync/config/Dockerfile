ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    python3 \
    ninja-build \
    meson \
    binutils \
    libzstd-dev \
    liblzma-dev \
    zlib1g-dev \
    libacl1-dev \
    libssl-dev \
    libcurl4-openssl-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Configure and build with Meson/Ninja
WORKDIR /fuzz/src
RUN meson setup build \
    --prefix=/fuzz/install \
    -Dbuildtype=release \
    -Dfuse=false \
    -Dselinux=false \
    -Dudev=false \
    -Dman=false \
    -Doss-fuzz=false -Dllvm-fuzz=false \
    -Dlibzstd=enabled -Dliblzma=enabled -Dlibz=enabled
RUN ninja -C build -j"$(nproc)" && ninja -C build install

# Manually install the static library, headers, and generated config.h for external builds
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp build/config.h /fuzz/install/include/config.h \
 && cp -a src/*.h /fuzz/install/include/ \
 && rm -f /fuzz/install/lib/libshared.a \
 && ar crs /fuzz/install/lib/libshared.a build/src/libshared.a.p/*.o \
 && ranlib /fuzz/install/lib/libshared.a
