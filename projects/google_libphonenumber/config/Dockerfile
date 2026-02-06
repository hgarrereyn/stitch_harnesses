ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    git \
    pkg-config \
    cmake \
    ninja-build \
    make \
    libicu-dev \
    libprotobuf-dev \
    protobuf-compiler \
    ca-certificates \
  && rm -rf /var/lib/apt/lists/*

# Configure, build and install libphonenumber (C++)
WORKDIR /fuzz/src
RUN mkdir -p build && cd build && \
    cmake -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_TESTING=OFF \
      -DBUILD_GEOCODER=OFF \
      -DBUILD_SHARED_LIBS=ON \
      -DBUILD_STATIC_LIB=OFF \
      -DUSE_BOOST=OFF \
      -DUSE_STDMUTEX=ON \
      -DREGENERATE_METADATA=OFF \
      ../cpp && \
    ninja -v install
