ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies: python3, pip, pkg-config; install modern meson via pip
# Also install system pixman to satisfy static cairo linkage
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 python3-pip pkg-config ca-certificates libpixman-1-dev \
 && rm -rf /var/lib/apt/lists/* \
 && python3 -m pip install --no-cache-dir --upgrade pip \
 && python3 -m pip install --no-cache-dir 'meson>=1.3.0,<1.6'

# Configure, build, and install cairo statically with minimal deps
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

# Use a separate build dir and install to /fuzz/install
RUN meson setup build \
      --prefix=/fuzz/install \
      --libdir=lib \
      --includedir=include \
      -Ddefault_library=static \
      -Dtests=disabled \
      -Dgtk_doc=false \
      -Dpng=disabled \
      -Dzlib=disabled \
      -Dfreetype=disabled \
      -Dfontconfig=disabled \
      -Dxcb=disabled \
      -Dxlib=disabled \
      -Dxlib-xcb=disabled \
      -Dquartz=disabled \
      -Dtee=disabled \
      -Dglib=disabled \
      -Dspectre=disabled \
      -Dlzo=disabled \
  && meson compile -C build \
  && meson install -C build
