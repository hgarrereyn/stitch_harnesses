ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        ca-certificates \
        curl \
    && rm -rf /var/lib/apt/lists/*

# Install xtl (headers only) satisfying dependency
WORKDIR /tmp
RUN curl -L -o xtl.tar.gz https://github.com/xtensor-stack/xtl/archive/refs/tags/0.8.0.tar.gz && \
    tar xf xtl.tar.gz && \
    mkdir -p /fuzz/install/include && \
    cp -r xtl-0.8.0/include/xtl /fuzz/install/include/

# Install xtensor 0.26.0 (headers only, C++17-compatible)
RUN curl -L -o xtensor.tar.gz https://github.com/xtensor-stack/xtensor/archive/refs/tags/0.26.0.tar.gz && \
    tar xf xtensor.tar.gz && \
    cp -r xtensor-0.26.0/include/xtensor /fuzz/install/include/

# Keep source tree mounted (no build step required for header-only)
WORKDIR /fuzz/src
