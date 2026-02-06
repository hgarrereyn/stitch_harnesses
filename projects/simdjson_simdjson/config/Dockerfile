ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && \
    apt-get install -y --no-install-recommends cmake make && \
    rm -rf /var/lib/apt/lists/*

# Build and install simdjson as a static library into /fuzz/install
RUN mkdir -p /fuzz/build /fuzz/install
WORKDIR /fuzz/build

# Configure with cmake using the provided clang wrappers and install prefix
RUN cmake -S /fuzz/src \
    -B /fuzz/build \
    -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DSIMDJSON_SINGLEHEADER=ON

# Build and install
RUN cmake --build /fuzz/build --target install -j$(nproc)
