ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for PHP and common libs
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    autoconf \
    bison \
    re2c \
    pkg-config \
    libxml2-dev \
    libsqlite3-dev \
    zlib1g-dev \
    libssl-dev \
    libcurl4-openssl-dev \
    libonig-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate configure scripts
RUN ./buildconf -f

# Configure minimal static embed library build
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure \
    --prefix=/fuzz/install \
    --enable-embed=static \
    --disable-all \
    --without-pear

# Build and install
RUN make -j"$(nproc)" && make install
