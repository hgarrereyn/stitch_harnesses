ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and minimal utilities for FetchContent
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates unzip cmake ninja-build make pkg-config golang-go \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Configure and build Tink (this fetches third-party deps via CMake)
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DTINK_BUILD_TESTS=OFF
RUN cmake --build /fuzz/build -j"$(nproc)"

# Install public headers and generated version header + util and module headers used by API
RUN set -eux; \
    mkdir -p /fuzz/install/include/tink; \
    cp /fuzz/src/cc/*.h /fuzz/install/include/tink/; \
    for d in util internal aead daead hybrid mac signature streamingaead config core monitoring; do \
      mkdir -p /fuzz/install/include/tink/${d}; \
      if ls /fuzz/src/cc/${d}/*.h >/dev/null 2>&1; then cp /fuzz/src/cc/${d}/*.h /fuzz/install/include/tink/${d}/; fi; \
    done; \
    cp /fuzz/build/__generated/tink/version.h /fuzz/install/include/tink/
