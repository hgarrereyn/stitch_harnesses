ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install zlib statically into /fuzz/install using configure/make
RUN apt-get update && apt-get install -y --no-install-recommends \
    make \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

RUN ./configure --static --prefix=/fuzz/install \
 && make -j$(nproc) \
 && make install
