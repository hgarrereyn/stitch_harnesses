ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    libssl-dev \
    ca-certificates \
    cmake \
    ninja-build \
    make \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/build

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DWITH_CLIENTS=OFF \
    -DWITH_BROKER=OFF \
    -DWITH_APPS=OFF \
    -DWITH_PLUGINS=OFF \
    -DDOCUMENTATION=OFF \
    -DWITH_STATIC_LIBRARIES=ON \
    -DBUILD_SHARED_LIBS=OFF \
 && cmake --build /fuzz/build --target install -- -v