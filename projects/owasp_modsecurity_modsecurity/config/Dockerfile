ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    git autoconf automake libtool pkg-config make g++ \
    libyajl-dev libpcre2-dev libxml2-dev liblmdb-dev libcurl4-openssl-dev libmaxminddb-dev ca-certificates \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Ensure git submodules (mbedtls, libinjection, tests) are present
RUN git submodule update --init --recursive

RUN ./build.sh \
    && ./configure --prefix=/fuzz/install --disable-examples \
    && make -j"$(nproc)" \
    && make install
