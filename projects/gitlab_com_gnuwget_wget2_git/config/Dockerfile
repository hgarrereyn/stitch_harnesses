ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools bootstrap and minimal libs
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config gettext autopoint \
    flex bison python3 rsync tar \
    lzip texinfo \
    libunistring-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
ENV PREFIX=/fuzz/install
WORKDIR /fuzz/src

# Bootstrap autotools, configure for static lib only with minimal feature set, build and install
RUN ./bootstrap && \
    ./configure \
      --prefix=${PREFIX} \
      --disable-shared --enable-static \
      --with-ssl=none \
      --without-libnghttp2 \
      --without-gpgme \
      --without-libmicrohttpd \
      --without-libproxy \
      --without-libhsts \
      --without-libdane \
      --without-brotlidec \
      --without-zstd \
      --without-lzip \
      --without-lzma \
      --without-libpcre \
      --without-libpcre2 \
      --without-libpsl \
      --without-libidn2 \
      --without-libidn \
      --disable-doc \
    && make -j"$(nproc)" \
    && make install
