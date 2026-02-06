ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    libssl-dev \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src/Linux
RUN chmod +x script/*.sh

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Build HP-Socket (disable brotli to avoid external dependency)
RUN ./script/compile.sh -d false -m system -b false -c gf_libafl_cxx

# Install to /fuzz/install with libraries under lib
RUN ./script/install.sh -p /fuzz/install -l lib -y
