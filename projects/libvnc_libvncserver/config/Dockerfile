ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
      cmake ninja-build make pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Configure and build
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DWITH_LIBVNCCLIENT=OFF \
    -DWITH_EXAMPLES=OFF \
    -DWITH_TESTS=OFF \
    -DWITH_QT=OFF \
    -DWITH_SDL=OFF \
    -DWITH_GTK=OFF \
    -DWITH_FFMPEG=OFF \
    -DWITH_SYSTEMD=OFF \
    -DWITH_LIBSSHTUNNEL=OFF \
    -DWITH_XCB=OFF \
    -DWITH_SASL=OFF \
    -DWITH_GNUTLS=OFF \
    -DWITH_OPENSSL=OFF \
    -DWITH_GCRYPT=OFF \
    -DWITH_JPEG=OFF \
    -DWITH_PNG=OFF \
    -DWITH_ZLIB=OFF \
    -DWITH_TIGHTVNC_FILETRANSFER=OFF \
    -DWITH_IPv6=ON \
    -DWITH_WEBSOCKETS=ON \
    -DWITH_LZO=OFF \
 && cmake --build /fuzz/build --target install -j$(nproc)
