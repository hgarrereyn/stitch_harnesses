ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install glog as a static library
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

RUN cmake -S /fuzz/src -B /fuzz/build \
      -G Ninja \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DBUILD_EXAMPLES=OFF \
      -DBUILD_TESTING=OFF \
      -DWITH_GTEST=OFF \
      -DWITH_GFLAGS=OFF \
      -DWITH_UNWIND=none \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  && cmake --build /fuzz/build --target install -- -v
