ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    libssl-dev \
    perl \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure with fuzzing compilers and static libs
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./configure \
      --prefix=/fuzz/install \
      --disable-shared \
      --enable-static \
      --with-defaults \
      --without-rpm \
      --disable-embedded-perl \
      --without-perl-modules \
      --disable-manuals \
      --disable-applications \
      --disable-mibs \
      --disable-scripts \
      --disable-agent || { cat config.log || true; exit 1; }

# Build and install
RUN make -j"$(nproc)" && make install
