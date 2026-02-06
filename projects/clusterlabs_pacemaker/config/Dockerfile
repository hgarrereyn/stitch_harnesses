ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for pacemaker
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config gettext autopoint \
    build-essential \
    libxml2-dev libxslt1-dev libglib2.0-dev libqb-dev libgnutls28-dev \
    libbz2-dev uuid-dev libpam0g-dev libdbus-1-dev libncurses-dev \
    libcpg-dev libcfg-dev libcmap-dev libquorum-dev libcorosync-common-dev \
    python3 python3-setuptools \
    xsltproc help2man \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
ENV PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Generate configure script
RUN ./autogen.sh

# Configure: prefer static libs when possible
RUN ./configure --prefix=${PREFIX} --disable-shared --enable-static

# Build and install
RUN make -j"$(nproc)" && make install
