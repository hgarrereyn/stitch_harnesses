ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    cmake \
    pkg-config \
    libpcre2-dev \
    zlib1g-dev \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build lighttpd
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Configure with CMake
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DWITH_PCRE2=ON \
    -DWITH_ZLIB=ON \
    -DWITH_LUA=OFF -DWITH_GNUTLS=OFF -DWITH_OPENSSL=OFF -DWITH_MBEDTLS=OFF -DWITH_WOLFSSL=OFF -DWITH_NSS=OFF -DWITH_BORINGSSL=OFF -DWITH_NETTLE=OFF \
    -DWITH_BZIP=OFF -DWITH_ZSTD=OFF -DWITH_BROTLI=OFF -DWITH_LIBDEFLATE=OFF -DWITH_MAXMINDDB=OFF -DWITH_PAM=OFF -DWITH_KRB5=OFF -DWITH_LDAP=OFF -DWITH_FAM=OFF -DWITH_MYSQL=OFF -DWITH_PGSQL=OFF -DWITH_DBI=OFF -DWITH_XXHASH=OFF -DWITH_WEBDAV_PROPS=OFF -DWITH_SQLITE3=OFF

RUN cmake --build /fuzz/build --target install -j$(nproc)

# Install headers for external use (and generated config.h)
RUN mkdir -p /fuzz/install/include/lighttpd && \
    cp -a /fuzz/src/src/*.h /fuzz/install/include/lighttpd/ && \
    cp -a /fuzz/build/build/config.h /fuzz/install/include/lighttpd/
