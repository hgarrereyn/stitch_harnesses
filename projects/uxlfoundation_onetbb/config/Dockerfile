ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools (ensure cmake/ninja available in base image)
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    pkg-config \
  && rm -rf /var/lib/apt/lists/*

# Configure and build oneTBB statically
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DTBB_TEST=OFF \
    -DTBB_EXAMPLES=OFF \
    -DTBB_ENABLE_IPO=OFF \
    -DTBB_STRICT=OFF \
    -DTBBMALLOC_PROXY_BUILD=OFF \
  && cmake --build /fuzz/build --target install -j"$(nproc)"
