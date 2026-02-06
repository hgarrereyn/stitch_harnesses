ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal build deps
RUN apt-get update && apt-get install -y --no-install-recommends make && rm -rf /var/lib/apt/lists/*

# Build static library with embedded mode to avoid external deps and -Werror
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc
ENV AR=ar
RUN make -j"$(nproc)" EMBEDDED_MODE=1 CC=${CC} AR=${AR} obj=build && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp build/libtpm2.a /fuzz/install/lib/ && \
    cp *.h /fuzz/install/include/ && \
    if [ -f tpm_simulator.hpp ]; then cp tpm_simulator.hpp /fuzz/install/include/; fi
