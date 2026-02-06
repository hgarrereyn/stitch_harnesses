ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for jq (autotools, flex, bison, libtool)
RUN apt-get update && apt-get install -y --no-install-recommends \
    autoconf automake libtool flex bison pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Build and install jq as a static library with builtin oniguruma
WORKDIR /fuzz/src
RUN autoreconf -fi
RUN CC=gf_libafl_cc CXX=gf_libafl_cxx \
    ./configure --disable-shared --enable-static \
    --with-oniguruma=builtin \
    --prefix=/fuzz/install
RUN make -j"$(nproc)"
RUN make install
