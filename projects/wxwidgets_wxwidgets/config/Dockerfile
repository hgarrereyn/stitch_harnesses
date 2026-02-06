ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (minimal, GUI disabled)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

# Build and install wxWidgets (base only, static)
WORKDIR /fuzz/build

# Out-of-tree build
RUN CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    /fuzz/src/configure \
      --prefix=/fuzz/install \
      --disable-shared \
      --disable-gui \
      --disable-mediactrl \
      --disable-webview \
      --without-gtk \
      --with-zlib=sys \
      --with-libpng=no \
      --with-libtiff=no \
      --with-libjpeg=no \
      --with-expat=builtin \
 && make -j"$(nproc)" \
 && make install \
 && setup_path=$(find /fuzz/install/lib/wx/include -name setup.h -print -quit) \
 && mkdir -p /fuzz/install/include/wx-3.3/wx \
 && cp "$setup_path" /fuzz/install/include/wx-3.3/wx/setup.h

# Show installation for debugging (optional, small)
RUN find /fuzz/install -maxdepth 3 -type f | sort | head -n 50
