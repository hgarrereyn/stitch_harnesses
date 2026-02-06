ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for ps3netsrv (meson, ninja, mbedtls)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    meson ninja-build pkg-config libmbedtls-dev ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

# Build and install ps3netsrv
WORKDIR /fuzz/src/_Projects_/ps3netsrv
RUN meson setup build --prefix=/fuzz/install \
 && meson compile -C build \
 && meson install -C build

# Install headers for development (not installed by meson)
RUN mkdir -p /fuzz/install/include/ps3netsrv \
 && cp -v include/*.h /fuzz/install/include/ps3netsrv/
