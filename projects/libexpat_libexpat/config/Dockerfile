ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, install static libexpat into /fuzz/install
RUN mkdir -p /fuzz/build && \
    cd /fuzz/build && \
    CC=gf_libafl_cc CXX=gf_libafl_cxx cmake -G Ninja \
      -S /fuzz/src/expat \
      -B . \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DEXPAT_ENABLE_INSTALL=ON \
      -DEXPAT_SHARED_LIBS=OFF \
      -DEXPAT_BUILD_TOOLS=OFF \
      -DEXPAT_BUILD_EXAMPLES=OFF \
      -DEXPAT_BUILD_TESTS=OFF \
      -DEXPAT_BUILD_DOCS=OFF \
      -DEXPAT_BUILD_PKGCONFIG=ON \
      -DEXPAT_BUILD_FUZZERS=OFF && \
    cmake --build . --parallel && \
    cmake --install .
