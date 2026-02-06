ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    make \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

# Build and install libzip
WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DLIBZIP_DO_INSTALL=ON \
    -DBUILD_DOC=OFF \
    -DBUILD_TOOLS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_OSSFUZZ=OFF \
    -DBUILD_REGRESS=OFF \
    -DENABLE_BZIP2=OFF \
    -DENABLE_LZMA=OFF \
    -DENABLE_ZSTD=OFF \
    -DENABLE_OPENSSL=OFF \
    -DENABLE_GNUTLS=OFF \
    -DENABLE_MBEDTLS=OFF \
    -DENABLE_WINDOWS_CRYPTO=OFF \
    -DENABLE_COMMONCRYPTO=OFF \
 && cmake --build build -j \
 && cmake --install build
