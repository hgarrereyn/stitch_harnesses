ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build
RUN cmake -G Ninja \
    -S /fuzz/src \
    -B /tmp/build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DSPOTIFY_JSON_BUILD_TESTS=OFF \
    -DBUILD_SHARED_LIBS=OFF \
 && cmake --build /tmp/build -j

# Manually "install": copy headers and static libs to /fuzz/install
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -r /fuzz/src/include/* /fuzz/install/include/ \
 && cp -r /fuzz/src/vendor/double-conversion/double-conversion /fuzz/install/include/ \
 && find /tmp/build -name "libspotify-json.a" -exec cp {} /fuzz/install/lib/ \; \
 && find /tmp/build -name "libdouble-conversion.a" -exec cp {} /fuzz/install/lib/ \; \
 && test -f /fuzz/install/lib/libspotify-json.a
