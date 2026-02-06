ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Use the fuzzer compiler wrappers
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

# Configure and build
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_TESTS=OFF \
    -DBUILD_TOOLS=OFF \
    -DBUILD_LIBWASM=OFF \
    -DBUILD_FUZZ_TOOLS=OFF \
    -DWABT_INSTALL_RULES=ON \
    -DWITH_WASI=OFF \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON && \
    cmake --build /fuzz/build --target install -j
