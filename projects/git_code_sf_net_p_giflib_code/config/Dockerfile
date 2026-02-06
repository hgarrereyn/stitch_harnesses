ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends xmlto imagemagick && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install
RUN make -j"$(nproc)" && make install PREFIX=${PREFIX}
