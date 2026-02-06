ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    libjpeg-turbo8-dev \
    ca-certificates \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure and build jpegoptim as a static library (BUILD_FUZZERS builds a lib target)
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx CFLAGS="-fno-lto" CXXFLAGS="-fno-lto"
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_FUZZERS=ON \
    -DUSE_MOZJPEG=0
RUN cmake --build /fuzz/build --target install -j

# Install public headers (project doesn't install headers by default)
RUN mkdir -p /fuzz/install/include \
 && cp /fuzz/src/jpegoptim.h /fuzz/src/jpegmarker.h /fuzz/install/include/
