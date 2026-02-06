ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Install build tools and dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    libbrotli-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and build woff2 statically
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install && \
    cmake --build /fuzz/build --target install -- -v
