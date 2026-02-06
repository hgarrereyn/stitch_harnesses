ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    libpcsclite-dev libssl-dev zlib1g-dev \
    ca-certificates make gcc g++ \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Bootstrap, configure (static), build and install
RUN ./bootstrap.ci || ./bootstrap && \
    ./configure --prefix=/fuzz/install \
      --disable-shared --enable-static \
      --disable-man --disable-doc \
      --disable-tests --disable-integration-tests \
      --disable-cmocka \
      --disable-openct --disable-ctapi --disable-cryptotokenkit \
      --enable-pcsc \
      --disable-openpace \
      --disable-notify \
    && make -j$(nproc) && make install

# Install headers for development: copy project headers to a stable include tree
RUN set -eux; \
    mkdir -p /fuzz/install/include/libopensc /fuzz/install/include/common /fuzz/install/include/scconf; \
    cp -a src/libopensc/*.h /fuzz/install/include/libopensc/; \
    cp -a src/common/*.h /fuzz/install/include/common/; \
    cp -a src/scconf/*.h /fuzz/install/include/scconf/;
