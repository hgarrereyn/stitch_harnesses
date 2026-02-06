ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (cmake, ninja) and any extras
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install tinyxml2 as a static library
WORKDIR /fuzz/build
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN cmake -G Ninja \
    -S /fuzz/src \
    -B /fuzz/build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -Dtinyxml2_BUILD_TESTING=OFF \
 && cmake --build /fuzz/build --target install
