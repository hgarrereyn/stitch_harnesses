ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    cmake ninja-build pkg-config build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Configure and build static libraries only
RUN cmake -S /fuzz/src -B /fuzz/build \
      -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DUPNP_BUILD_SHARED=OFF \
      -DUPNP_BUILD_STATIC=ON \
      -DBUILD_TESTING=OFF \
  && cmake --build /fuzz/build --target install -j
