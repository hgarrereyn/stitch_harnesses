ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal dependencies for building and linking
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    binutils \
    pkg-config \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Build and install Janet
ENV PREFIX=/fuzz/install
RUN make -j"$(nproc)" \
      CC=gf_libafl_cc HOSTCC=gf_libafl_cc \
      AR=llvm-ar-17 HOSTAR=llvm-ar-17 \
      PREFIX=${PREFIX} \
  && make install PREFIX=${PREFIX}
