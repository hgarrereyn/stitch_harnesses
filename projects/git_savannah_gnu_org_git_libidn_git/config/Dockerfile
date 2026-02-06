ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools project
RUN apt-get update && apt-get install -y --no-install-recommends \
    autoconf automake libtool gettext autopoint pkg-config perl gperf gengetopt \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libidn (static-only if possible)
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src
RUN ./bootstrap && \
    ./configure --disable-doc --disable-shared --enable-static --prefix=/fuzz/install \
    && make -j$(nproc) \
    && make install
