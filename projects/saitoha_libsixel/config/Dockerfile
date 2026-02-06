ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal dependencies for Autotools build
RUN apt-get update && apt-get install -y --no-install-recommends \
    pkg-config \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure and build static-only libsixel without optional external deps
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./configure \
    --prefix=/fuzz/install \
    --disable-shared --enable-static \
    --without-libcurl --without-gd --without-gdk-pixbuf2 \
    --without-jpeg --without-png \
    --disable-python \
    --disable-gcov \
    --disable-tests && \
    make -j"$(nproc)" && \
    make install
