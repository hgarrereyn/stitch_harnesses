ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    zlib1g-dev \
    libgnutls28-dev \
    libssl-dev \
    libavahi-client-dev \
    libavahi-common-dev \
    libusb-1.0-0-dev \
    libpam0g-dev \
    libsystemd-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install CUPS (static preferred)
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./configure --prefix=/fuzz/install --disable-shared --enable-static || (cat config.log || true; false)
RUN make -j"$(nproc)"
RUN make install
# Ensure headers are available under the install prefix for fuzzing
RUN mkdir -p /fuzz/install/include/cups && cp -a cups/*.h /fuzz/install/include/cups/

