ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and crypto dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        cmake \
        ninja-build \
        make \
        pkg-config \
        libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libsrtp (static)
WORKDIR /fuzz

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DCRYPTO_LIBRARY=openssl \
      -DLIBSRTP_TEST_APPS=OFF \
    && cmake --build /fuzz/build --target install --config Release
