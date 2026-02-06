ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and required libraries
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkgconf gettext autopoint \
    make \
    libmicrohttpd-dev libjpeg-dev zlib1g-dev \
    libavformat-dev libavcodec-dev libavutil-dev libswscale-dev libavdevice-dev \
  && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

# Regenerate build system, configure, build, and install
RUN autoreconf -fi && \
    ./configure --prefix=/fuzz/install --without-opencv --without-alsa --without-pulse --without-sqlite3 --without-mysql --without-pgsql --without-mariadb --without-fftw3 --without-libcam --with-webp=no && \
    make -j$(nproc) && \
    make install && \
    mkdir -p /fuzz/install/include/motion && \
    cp -v src/*.hpp /fuzz/install/include/motion/ && \
    cp -v config.hpp /fuzz/install/include/motion/
