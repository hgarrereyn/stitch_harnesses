ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    python3 \
    pkg-config \
    ninja-build \
    cmake \
    make \
    git \
    && rm -rf /var/lib/apt/lists/*

# Fetch third-party dependencies as specified by shaderc (requires network)
WORKDIR /fuzz/src
RUN ./utils/git-sync-deps

# Configure, build and install
WORKDIR /fuzz/build
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN cmake -GNinja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DSHADERC_SKIP_TESTS=ON \
    -DSHADERC_SKIP_EXAMPLES=ON \
    -DSHADERC_SKIP_EXECUTABLES=ON \
    -DSHADERC_ENABLE_WERROR_COMPILE=OFF \
    /fuzz/src && \
    ninja install
