ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools and iconv macros
RUN apt-get update && apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config gettext autopoint autoconf-archive \
    make ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate build system
RUN autoreconf -i -f

# Configure with fuzzing compilers and install prefix
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure --prefix=/fuzz/install

# Build and install
RUN make -j"$(nproc)" && make install
