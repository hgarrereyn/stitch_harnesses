ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies for libvips and meson
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    meson \
    ninja-build \
    pkg-config \
    libglib2.0-dev \
    libexpat1-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig${PKG_CONFIG_PATH:+:$PKG_CONFIG_PATH}

WORKDIR /fuzz/src

# Configure, build, and install static libvips with most optional features disabled
RUN meson setup build \
      --prefix /fuzz/install \
      --libdir lib \
      --default-library static \
      --buildtype release \
      -Dmodules=disabled \
      -Dintrospection=disabled \
      -Dexamples=false \
      -Ddocs=false \
      -Dcpp-docs=false \
      -Dvapi=false \
      -Dcfitsio=disabled \
      -Dcgif=disabled \
      -Dexif=disabled \
      -Dfftw=disabled \
      -Dfontconfig=disabled \
      -Darchive=disabled \
      -Dheif=disabled \
      -Dimagequant=disabled \
      -Djpeg=disabled \
      -Duhdr=disabled \
      -Djpeg-xl=disabled \
      -Dlcms=disabled \
      -Dmagick=disabled \
      -Dmatio=disabled \
      -Dnifti=disabled \
      -Dopenexr=disabled \
      -Dopenjpeg=disabled \
      -Dopenslide=disabled \
      -Dhighway=disabled \
      -Dorc=disabled \
      -Dpangocairo=disabled \
      -Dpdfium=disabled \
      -Dpng=disabled \
      -Dpoppler=disabled \
      -Dquantizr=disabled \
      -Draw=disabled \
      -Drsvg=disabled \
      -Dspng=disabled \
      -Dtiff=disabled \
      -Dwebp=disabled \
      -Dzlib=disabled \
    && meson compile -C build \
    && meson install -C build
