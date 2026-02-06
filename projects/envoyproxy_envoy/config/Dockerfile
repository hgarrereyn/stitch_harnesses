ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies required to use Envoy headers (Abseil)
RUN apt-get update && apt-get install -y --no-install-recommends \
    libabsl-dev \
 && rm -rf /var/lib/apt/lists/*

# Create install prefix
ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include

# "Install" headers needed for using small header-only parts of Envoy.
COPY . /fuzz/src
RUN set -eux; \
    mkdir -p ${PREFIX}/include/envoy ${PREFIX}/include/source/common/common; \
    cp -r /fuzz/src/envoy ${PREFIX}/include/; \
    cp -r /fuzz/src/source/common/common ${PREFIX}/include/source/common/;

# Environment for compilers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
