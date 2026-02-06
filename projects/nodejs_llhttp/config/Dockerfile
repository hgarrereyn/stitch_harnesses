ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install Node.js 20 (for tsx/TypeScript generator) and build deps
RUN apt-get update && apt-get install -y --no-install-recommends curl ca-certificates gnupg make pkg-config && \
    curl -fsSL https://deb.nodesource.com/setup_20.x | bash - && \
    apt-get install -y --no-install-recommends nodejs && \
    rm -rf /var/lib/apt/lists/*

# Build llhttp and install static artifacts
WORKDIR /fuzz/src

# Install JS deps and generate C sources
RUN npm ci && \
    make build/libllhttp.a CLANG=gf_libafl_cc && \
    mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp build/llhttp.h /fuzz/install/include/llhttp.h && \
    cp build/libllhttp.a /fuzz/install/lib/
