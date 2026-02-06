ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
    zlib1g-dev \
  && rm -rf /var/lib/apt/lists/*

# Configure, build and install minizip-ng as static library
WORKDIR /fuzz/src

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DMZ_BUILD_TESTS=OFF \
    -DMZ_BUILD_UNIT_TESTS=OFF \
    -DMZ_BUILD_FUZZ_TESTS=OFF \
    -DMZ_BZIP2=OFF \
    -DMZ_LZMA=OFF \
    -DMZ_ZSTD=OFF \
    -DMZ_OPENSSL=OFF \
    -DMZ_LIBBSD=OFF \
    -DMZ_LIBCOMP=OFF \
    -DMZ_ICONV=OFF

RUN cmake --build build --target install -- -v
