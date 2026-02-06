ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    autoconf automake libtool autoconf-archive \
    make ninja-build \
    g++ \
    protobuf-compiler libprotobuf-dev \
    libqb-dev \
    libsodium-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Generate build system and configure
RUN ./autogen.sh && \
    ./configure \
      --prefix=${PREFIX} \
      --disable-shared --enable-static \
      --with-dbus=no \
      --with-polkit=no \
      --with-bundled-catch \
      --with-bundled-pegtl

# Build and install
RUN make -j"$(nproc)" && make install
