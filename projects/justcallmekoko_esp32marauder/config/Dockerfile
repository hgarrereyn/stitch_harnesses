ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any extra dependencies (none required for header-only use)
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

# Set compilers as required
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Install headers into /fuzz/install since this project is Arduino-specific and lacks a host build
RUN mkdir -p /fuzz/install/include && \
    cp -v /fuzz/src/esp32_marauder/configs.h /fuzz/install/include/ && \
    cp -v /fuzz/src/esp32_marauder/Keyboard_def.h /fuzz/install/include/
