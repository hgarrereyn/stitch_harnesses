ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for building with CMake/Ninja
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    CFLAGS="-O2" \
    CXXFLAGS="-O2"

WORKDIR /fuzz/src

# Configure and build static-only PCRE2 (8-bit API only), no tests/tools/JIT
RUN cmake -G Ninja -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_STATIC_LIBS=ON \
    -DPCRE2_BUILD_PCRE2_8=ON \
    -DPCRE2_BUILD_PCRE2_16=OFF \
    -DPCRE2_BUILD_PCRE2_32=OFF \
    -DPCRE2_SUPPORT_JIT=OFF \
    -DPCRE2_BUILD_TESTS=OFF \
    -DPCRE2_BUILD_PCRE2GREP=OFF \
 && cmake --build build --target install --config Release
