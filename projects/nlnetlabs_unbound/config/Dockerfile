ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates flex bison libssl-dev libexpat1-dev pkg-config && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./configure --prefix=/fuzz/install --without-libevent && make -j"$(nproc)" && make install
