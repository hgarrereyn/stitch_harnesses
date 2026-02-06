ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (cmake, ninja) and runtime helpers
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    python3 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure and build (static libs)
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DQUICK_LINT_JS_ENABLE_CLI=OFF \
    -DQUICK_LINT_JS_ENABLE_BUILD_TOOLS=ON
RUN cmake --build build -j

# Install headers and static libraries
RUN mkdir -p /fuzz/install/include/quick-lint-js /fuzz/install/lib \
    && cd src/quick-lint-js \
    && find . -type d -exec mkdir -p /fuzz/install/include/quick-lint-js/{} \; \
    && find . -type f -name '*.h' -exec sh -c 'for f; do d=$(dirname "$f"); cp "$f" "/fuzz/install/include/quick-lint-js/$d/"; done' sh {} + \
    && find /fuzz/src/build -maxdepth 2 -type f -name 'libquick-lint-js*.a' -exec cp {} /fuzz/install/lib/ \; \
    && find /fuzz/src/build -type f -name 'libsimdjson.a' -exec cp {} /fuzz/install/lib/ \;
