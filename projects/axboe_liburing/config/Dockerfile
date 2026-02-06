ARG BASE_IMAGE
FROM ${BASE_IMAGE}

WORKDIR /fuzz/src

RUN ./configure --cc=gf_libafl_cc --cxx=gf_libafl_cxx --prefix=/fuzz/install

RUN make -C src -j"$(nproc)" ENABLE_SHARED=0 \
 && make -j"$(nproc)" ENABLE_SHARED=0 install prefix=/fuzz/install
