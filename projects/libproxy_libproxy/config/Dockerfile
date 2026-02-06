ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    meson pkg-config ninja-build \
    libglib2.0-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Configure with Meson, disable optional features to minimize dependencies
RUN meson setup build \
    --prefix=/fuzz/install \
    -Ddocs=false -Dtests=false -Dintrospection=false -Dvapi=false \
    -Dconfig-gnome=false -Dconfig-kde=false -Dconfig-xdp=false \
    -Dconfig-osx=false -Dconfig-windows=false \
    -Dpacrunner-duktape=false -Dcurl=false

RUN meson compile -C build -j$(nproc)
RUN meson install -C build
