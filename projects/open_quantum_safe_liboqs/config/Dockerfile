ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Install minimal build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
      cmake ninja-build pkg-config \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

RUN cmake -S . -B build \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/fuzz/install \
        -DBUILD_SHARED_LIBS=OFF \
        -DOQS_BUILD_ONLY_LIB=ON \
        -DOQS_USE_OPENSSL=OFF \
        -GNinja \
    && cmake --build build -j \
    && cmake --install build
