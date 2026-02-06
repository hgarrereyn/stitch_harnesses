ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install google/cctz as a static library into /fuzz/install
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure: disable tests/tools/examples; prefer static libs; set install prefix
RUN cmake -S . -B /fuzz/build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_TESTING=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_TOOLS=OFF \
    -DBUILD_SHARED_LIBS=OFF

RUN cmake --build /fuzz/build --target install
