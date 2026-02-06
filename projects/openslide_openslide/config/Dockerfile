ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    meson pkg-config \
    libcairo2-dev libglib2.0-dev \
    libjpeg-turbo8-dev libpng-dev libtiff-dev libxml2-dev \
    libopenjp2-7-dev libsqlite3-dev zlib1g-dev libzstd-dev \
    ca-certificates findutils \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install OpenSlide statically
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src
RUN meson setup builddir \
      --buildtype=release \
      --prefix=/fuzz/install \
      --default-library=static \
      -Ddoc=disabled -Dtest=disabled && \
    meson compile -C builddir && \
    mkdir -p /fuzz/install/lib && \
    # If libdicom was built as a Meson subproject, copy its static library for external linking
    find builddir -name "libdicom*.a" -exec cp -v {} /fuzz/install/lib/ \; || true && \
    meson install -C builddir
