ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    DEBIAN_FRONTEND=noninteractive

# Install minimal build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src/build

RUN cmake -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -Dimmer_BUILD_TESTS=OFF \
    -Dimmer_BUILD_EXAMPLES=OFF \
    -Dimmer_BUILD_DOCS=OFF \
    -Dimmer_BUILD_EXTRAS=OFF \
    .. \
 && cmake --build . --target install
