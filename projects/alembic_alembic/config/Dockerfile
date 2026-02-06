ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make \
    libimath-dev \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

WORKDIR /fuzz/build

RUN cmake -G Ninja -S /fuzz/src -B . \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DALEMBIC_SHARED_LIBS=OFF \
    -DUSE_HDF5=OFF \
    -DUSE_BINARIES=OFF \
    -DUSE_TESTS=OFF \
    -DUSE_EXAMPLES=OFF \
 && cmake --build . --target install
