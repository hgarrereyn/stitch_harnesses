ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for building pjproject
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    libssl-dev \
    uuid-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install pjproject (static libs) using autoconf/make
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

RUN ./configure --prefix=/fuzz/install --disable-shared && \
    make dep -j$(nproc) && \
    make -j$(nproc) && \
    make install
