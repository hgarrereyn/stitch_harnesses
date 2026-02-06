ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies to build libssh2 with OpenSSL backend
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    libssl-dev \
  && rm -rf /var/lib/apt/lists/*

# Build and install libssh2 (static only)
ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_STATIC_LIBS=ON \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCRYPTO_BACKEND=OpenSSL \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_TESTING=OFF \
    -DLIBSSH2_BUILD_DOCS=OFF \
  && cmake --build /fuzz/build --target install --config Release
