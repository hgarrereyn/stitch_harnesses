ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake ninja-build make pkg-config \
 && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /build && \
    cmake -G Ninja -S /fuzz/src -B /build \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DGC_BUILD_SHARED_LIBS=OFF \
      -DBUILD_TESTING=OFF \
    && cmake --build /build --target install
