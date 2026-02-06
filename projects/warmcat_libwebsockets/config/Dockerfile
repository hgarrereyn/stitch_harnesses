ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libwebsockets statically with minimal deps
WORKDIR /fuzz/src
RUN cmake -S . -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_INSTALL_LIBDIR=lib \
    -DCMAKE_BUILD_TYPE=Release \
    -DLWS_WITH_STATIC=ON \
    -DLWS_WITH_SHARED=OFF \
    -DLWS_WITH_SSL=OFF \
    -DLWS_WITH_HTTP2=OFF \
    -DLWS_WITH_ZLIB=OFF \
    -DLWS_WITH_MINIZ=OFF \
    -DLWS_WITH_MINIMAL_EXAMPLES=OFF \
    -DLWS_WITHOUT_TESTAPPS=ON \
    -DLWS_WITH_LIBEVENT=OFF \
    -DLWS_WITH_LIBEV=OFF \
    -DLWS_WITH_LIBUV=OFF \
    -DLWS_WITH_GLIB=OFF \
    -DLWS_WITH_SDEVENT=OFF \
    -DLWS_WITH_ULOOP=OFF
RUN cmake --build /fuzz/build --target install
