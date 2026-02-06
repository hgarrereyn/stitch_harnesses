ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools (ensure cmake and ninja are available) and pkg-config
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install static libwebsockets without external deps
WORKDIR /fuzz/src

RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DLWS_WITH_SSL=OFF \
    -DLWS_WITH_HTTP2=OFF \
    -DLWS_WITH_LIBUV=OFF \
    -DLWS_WITH_LIBEVENT=OFF \
    -DLWS_WITH_LIBEV=OFF \
    -DLWS_WITH_GLIB=OFF \
    -DLWS_WITH_LWSWS=OFF \
    -DLWS_WITH_MINIMAL_EXAMPLES=OFF \
    -DLWS_WITH_PLUGINS=OFF \
    -DLWS_WITH_PLUGINS_API=OFF \
    -DLWS_WITH_EVLIB_PLUGINS=OFF \
    -DLWS_WITH_SQLITE3=OFF \
    -DLWS_WITH_FTS=OFF \
    -DLWS_WITH_LIBCAP=OFF \
    -DLWS_WITH_JOSE=OFF \
    -DLWS_WITH_COSE=OFF \
    -DLWS_WITH_GENCRYPTO=OFF \
    -DLWS_WITH_SHARED=OFF \
    -DLWS_WITH_STATIC=ON \
    -DLWS_WITH_ZLIB=OFF \
    -DLWS_WITH_BUNDLED_ZLIB=OFF \
    -DLWS_WITHOUT_TESTAPPS=ON \
    -DLWS_WITH_HTTP_STREAM_COMPRESSION=OFF \
    -DLWS_WITH_HTTP_BROTLI=OFF \
    -DLWS_WITH_THREADPOOL=OFF \
    -DLWS_WITH_SELFTESTS=OFF

RUN cmake --build build --target install
