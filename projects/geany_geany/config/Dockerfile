ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for Geany (GTK3, GLib, etc.) and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    gettext \
    meson \
    ninja-build \
    libgtk-3-dev \
    libglib2.0-dev \
    libpango1.0-dev \
    libatk1.0-dev \
    libgdk-pixbuf-2.0-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Configure, build and install with Meson
WORKDIR /fuzz/src
RUN meson setup build \
    --prefix /fuzz/install \
    -Dhtml-docs=disabled -Dpdf-docs=disabled -Dapi-docs=disabled -Dgtkdoc=false \
    -Dvte=false -Dplugins=false -Dsocket=false \
    --buildtype release
RUN meson compile -C build
RUN meson install -C build

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig:$PKG_CONFIG_PATH
