ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates cmake ninja-build make pkg-config libssl-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

RUN mkdir -p build && cd build && \
    cmake .. -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DBUILD_TESTS=OFF \
      -DBUILD_EXAMPLES=OFF \
      -DUSE_SSH=OFF \
      -DUSE_HTTPS=OpenSSL \
      -DREGEX_BACKEND=builtin \
      -DUSE_HTTP_PARSER=builtin \
      -DUSE_BUNDLED_ZLIB=ON \
    && cmake --build . --target install -j$(nproc)
