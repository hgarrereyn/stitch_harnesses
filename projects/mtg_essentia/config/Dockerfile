ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python-is-python3 \
    pkg-config \
    libeigen3-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./waf configure --prefix=/fuzz/install --build-static --lightweight= --fft=KISS \
 && ./waf -j"$(nproc)" \
 && ./waf install
