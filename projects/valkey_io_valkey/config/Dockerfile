ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends cmake make ninja-build pkg-config && rm -rf /var/lib/apt/lists/*

# Build and install libvalkey (client library) statically
RUN cmake -S /fuzz/src/deps/libvalkey -B /tmp/build \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DDISABLE_TESTS=ON && \
    cmake --build /tmp/build --target install -j"$(nproc)"
