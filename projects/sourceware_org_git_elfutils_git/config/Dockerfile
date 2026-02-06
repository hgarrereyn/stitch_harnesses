ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config gettext autopoint gawk flex bison m4 \
    zlib1g-dev libbz2-dev liblzma-dev libzstd-dev ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build and install elfutils
WORKDIR /fuzz/src
RUN autoreconf -i -f
RUN CC=gf_libafl_cc CXX=gf_libafl_cxx \
    ./configure --enable-maintainer-mode --disable-debuginfod --disable-libdebuginfod \
    --prefix=/fuzz/install
RUN make -j"$(nproc)"
RUN make install
