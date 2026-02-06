ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    autoconf \
    automake \
    pkg-config \
    libtool \
    zlib1g-dev \
  && ln -sf /usr/bin/aclocal /usr/local/bin/aclocal-1.18 \
  && ln -sf /usr/bin/automake /usr/local/bin/automake-1.18 \
  && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

RUN ./configure \
    --prefix=/fuzz/install \
    --disable-all \
    --enable-mfsbdev \
    --disable-shared \
    --enable-static

RUN make -j$(nproc) && make install
