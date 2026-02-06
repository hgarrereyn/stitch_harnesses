ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure and build libarchive as a static library with minimal deps
WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DENABLE_TEST=OFF \
    -DENABLE_INSTALL=ON \
    -DENABLE_TAR=OFF \
    -DENABLE_CPIO=OFF \
    -DENABLE_CAT=OFF \
    -DENABLE_UNZIP=OFF \
    -DENABLE_ZLIB=OFF \
    -DENABLE_BZip2=OFF \
    -DENABLE_LZMA=OFF \
    -DENABLE_ZSTD=OFF \
    -DENABLE_LZ4=OFF \
    -DENABLE_LZO=OFF \
    -DENABLE_LIBB2=OFF \
    -DENABLE_OPENSSL=OFF \
    -DENABLE_MBEDTLS=OFF \
    -DENABLE_NETTLE=OFF \
    -DENABLE_LIBXML2=OFF \
    -DENABLE_EXPAT=OFF \
    -DENABLE_PCREPOSIX=OFF \
    -DENABLE_PCRE2POSIX=OFF \
    -DENABLE_XATTR=OFF \
    -DENABLE_ACL=OFF \
    -DENABLE_ICONV=OFF
RUN cmake --build build --target install -- -v
