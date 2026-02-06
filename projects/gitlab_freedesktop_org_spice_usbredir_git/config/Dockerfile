ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    meson \
    ninja-build \
    pkg-config \
    libusb-1.0-0-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build and install with meson (static libs, no tools/tests)
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src
RUN meson setup build \
      --prefix=/fuzz/install \
      -Ddefault_library=static \
      -Dtools=disabled \
      -Dtests=disabled \
      -Dfuzzing=disabled \
    && meson compile -C build \
    && meson install -C build
