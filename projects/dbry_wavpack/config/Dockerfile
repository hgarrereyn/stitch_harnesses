ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools (cmake may not be present in some bases)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure and build static libwavpack only
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DWAVPACK_BUILD_PROGRAMS=OFF \
    -DWAVPACK_ENABLE_ASM=OFF

RUN cmake --build build --target install --config Release
