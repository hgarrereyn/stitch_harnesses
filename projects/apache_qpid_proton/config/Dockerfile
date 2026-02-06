ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    pkg-config \
    cmake \
    ninja-build \
    make \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Configure, build and install from the project root. Build only the C libs with minimal deps.
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_TESTING=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_TOOLS=OFF \
    -DBUILD_STATIC_LIBS=ON \
    -DENABLE_WARNING_ERROR=OFF \
    -DSSL_IMPL=none \
    -DSASL_IMPL=none \
    -DPROACTOR=none \
    -DBUILD_CPP=OFF \
    -DBUILD_GO=OFF \
    -DBUILD_PYTHON=OFF \
    -DBUILD_RUBY=OFF
RUN cmake --build /fuzz/build --target install -- -v
