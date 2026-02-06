ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools project
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config gettext \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install static libmdb without optional deps
WORKDIR /fuzz/src
RUN autoreconf -i -f
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./configure \
      --prefix=/fuzz/install \
      --disable-shared --enable-static \
      --disable-man \
      --disable-glib \
      --disable-iconv \
    && make -j"$(nproc)" \
    && make install
