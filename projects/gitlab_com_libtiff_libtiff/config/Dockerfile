ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build libtiff statically with minimal external deps disabled
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Configure, build, install
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -Dtiff-static=ON \
    -Dtiff-tools=OFF \
    -Dtiff-tests=OFF \
    -Dtiff-contrib=OFF \
    -Dtiff-docs=OFF \
    -Dzlib=OFF \
    -Dlibdeflate=OFF \
    -Dpixarlog=OFF \
    -Djpeg=OFF \
    -Djpeg12=OFF \
    -Djbig=OFF \
    -Dlerc=OFF \
    -Dlzma=OFF \
    -Dzstd=OFF \
    -Dwebp=OFF \
 && cmake --build /fuzz/build --target install --config Release
