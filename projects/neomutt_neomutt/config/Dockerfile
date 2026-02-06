ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    pkg-config \
    libncursesw5-dev \
    libidn2-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

RUN ./configure \
      --prefix=/fuzz/install \
      --disable-doc \
      --disable-nls \
      --disable-pgp \
      --disable-smime \
    && make -j"$(nproc)" \
    && make install \
    && mkdir -p /fuzz/install/lib /fuzz/install/include/mutt \
    && cp libmutt.a /fuzz/install/lib/ \
    && cp mutt/*.h /fuzz/install/include/mutt/ \
    && cp config.h /fuzz/install/include/
