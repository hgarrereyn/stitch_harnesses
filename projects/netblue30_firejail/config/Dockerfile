ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends pkg-config gawk make sed coreutils findutils && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

RUN ./configure --prefix=/fuzz/install && \
    make -j"$(nproc)" && \
    make install && \
    mkdir -p /fuzz/install/include/firejail /fuzz/install/include/include && \
    cp -a src/include/*.h /fuzz/install/include/firejail/ && \
    cp -a src/include/*.h /fuzz/install/include/include/
