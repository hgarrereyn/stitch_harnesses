ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Configure with a minimal feature set to avoid external deps
RUN ./configure \
    --prefix=/fuzz/install \
    --disable-nls \
    --disable-curses \
    --disable-ncurses \
    --disable-ipv6

# Build
RUN make -j"$(nproc)"

# Install headers (and pkg-config metadata) into /fuzz/install
RUN make install-headers install-pkgconfig
