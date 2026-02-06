ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool \
    bison m4 gettext autopoint help2man texinfo \
    pkg-config \
    flex \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
RUN ./autogen.sh
RUN CC=gf_libafl_cc CXX=gf_libafl_cxx ./configure --prefix=/fuzz/install --disable-shared --enable-static --disable-bootstrap
RUN make -j"$(nproc)"
RUN make install
