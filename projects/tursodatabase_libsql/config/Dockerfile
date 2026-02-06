ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    ca-certificates \
    tcl \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src/libsql-sqlite3

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./configure --prefix=/fuzz/install --disable-shared --enable-static \
    --disable-readline --disable-editline

RUN make -j"$(nproc)" && make install
