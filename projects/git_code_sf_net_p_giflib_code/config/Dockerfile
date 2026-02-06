ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends xmlto imagemagick && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install
RUN make -j"$(nproc)" && make install PREFIX=${PREFIX}
