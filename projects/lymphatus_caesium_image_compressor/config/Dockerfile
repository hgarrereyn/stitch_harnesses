ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies to build Rust libcaesium
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates curl git pkg-config cargo rustc \
    && rm -rf /var/lib/apt/lists/*

# Create install prefix
RUN mkdir -p /fuzz/install/include /fuzz/install/lib

# Build libcaesium from the version specified in the repository
WORKDIR /tmp
RUN set -eux; \
    LIBCAESIUM_VERSION=$(cat /fuzz/src/libcaesium.conf); \
    git clone --depth 1 --branch ${LIBCAESIUM_VERSION} https://github.com/Lymphatus/libcaesium.git; \
    cd libcaesium; \
    cargo build --release; \
    cp target/release/libcaesium.so /fuzz/install/lib/

# Install public header from this repo
RUN install -m 0644 /fuzz/src/src/include/libcaesium.h /fuzz/install/include/

# Environment for compilers and install prefix (not used directly since we build Rust lib)
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install
