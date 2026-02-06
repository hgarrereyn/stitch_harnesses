ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    libssl-dev \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Build the crypto library (shared) and install headers and library
WORKDIR /fuzz/src/crypto

# Build the shared library provided by the project Makefile
RUN make clean && \
    make -j"$(nproc)" VALGRIND=0 tests/libtrezor-crypto.so

# Install artifacts
RUN mkdir -p /fuzz/install/lib \
    /fuzz/install/include/trezor-crypto/chacha20poly1305 \
    /fuzz/install/include/trezor-crypto/monero \
    /fuzz/install/include/trezor-crypto/ed25519-donna \
    /fuzz/install/include/vendor/secp256k1-zkp/include && \
    cp tests/libtrezor-crypto.so /fuzz/install/lib/libtrezor-crypto.so && \
    cp -a *.h /fuzz/install/include/trezor-crypto/ && \
    cp -a chacha20poly1305/*.h /fuzz/install/include/trezor-crypto/chacha20poly1305/ && \
    cp -a monero/*.h /fuzz/install/include/trezor-crypto/monero/ && \
    cp -a ed25519-donna/*.h /fuzz/install/include/trezor-crypto/ed25519-donna/ && \
    cp -a ../vendor/secp256k1-zkp/include/*.h /fuzz/install/include/vendor/secp256k1-zkp/include/

# Print what we installed (debug)
RUN ls -R /fuzz/install
