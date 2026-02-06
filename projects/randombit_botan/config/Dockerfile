ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    pkg-config \
    zlib1g-dev \
    libbz2-dev \
    liblzma-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure Botan to install into /fuzz/install, using the fuzzing compiler, and build static lib only
RUN python3 ./configure.py \
    --cc-bin=${CXX} \
    --prefix=/fuzz/install \
    --disable-shared

RUN make -j"$(nproc)" && make install
