ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (ensure cmake/make available)
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    make \
 && rm -rf /var/lib/apt/lists/*

# Configure and build Jansson as a static library, install to /fuzz/install
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN cmake -S /fuzz/src -B /tmp/build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DJANSSON_BUILD_SHARED_LIBS=OFF \
    -DJANSSON_BUILD_DOCS=OFF \
    -DJANSSON_WITHOUT_TESTS=ON \
    -DJANSSON_EXAMPLES=OFF \
 && cmake --build /tmp/build -j \
 && cmake --install /tmp/build
