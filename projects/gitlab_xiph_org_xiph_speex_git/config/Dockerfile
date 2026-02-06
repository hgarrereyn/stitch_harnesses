ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    meson \
    ninja-build \
    pkg-config \
    ca-certificates \
  && rm -rf /var/lib/apt/lists/*

# Configure, build, and install Speex as a static library
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Use Meson to configure a static build and install to /fuzz/install
RUN meson setup build \
      --prefix=/fuzz/install \
      -Ddefault_library=static \
      -Dtools=disabled \
      -Dtest-binaries=disabled \
      -Dfft=smallft \
    && ninja -C build -v \
    && ninja -C build -v install \
    && rm -rf build
