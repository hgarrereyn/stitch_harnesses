ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies for ImageMagick (no delegates, static only)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libtool \
    pkg-config \
    zlib1g-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure static build with minimal external dependencies
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./configure \
    --prefix=/fuzz/install \
    --disable-shared \
    --enable-static \
    --without-modules \
    --without-perl \
    --without-x \
    --without-xml \
    --without-lcms \
    --without-lqr \
    --without-openjp2 \
    --without-jbig \
    --without-heic \
    --without-webp \
    --without-pango \
    --without-freetype \
    --without-fontconfig \
    --without-raw \
    --without-djvu \
    --without-gvc \
    --disable-openmp

RUN make -j"$(nproc)" && make install
