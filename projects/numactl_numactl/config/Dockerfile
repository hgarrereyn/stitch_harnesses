ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools project
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate build system files (in case Makefile.in is not present)
RUN ./autogen.sh || true

# Configure with fuzzing compilers and install prefix; build static lib only
RUN CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    ./configure --prefix=/fuzz/install --enable-static --disable-shared

# Build and install
RUN make -j"$(nproc)" && make install
