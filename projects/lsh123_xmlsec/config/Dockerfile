ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    automake autoconf libtool pkg-config \
    libxml2-dev libxslt1-dev \
    libssl-dev libltdl-dev \
    && rm -rf /var/lib/apt/lists/*

# Build and install xmlsec (OpenSSL backend only)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src
RUN ./autogen.sh \
    --prefix=/fuzz/install \
    --with-openssl \
    --with-default-crypto=openssl \
    --with-gnutls=no --with-nss=no --with-gcrypt=no \
    --enable-docs=no --enable-mans=no --enable-apps=no \
    && make -j$(nproc) && make install
