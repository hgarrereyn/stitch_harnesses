ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Build static core library via CMake
WORKDIR /fuzz/build

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

RUN cmake -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_FLAGS="-I/fuzz/src/ext -I/fuzz/src/ext/prometheus-cpp-lite-1.0/core/include -I/fuzz/src/ext/prometheus-cpp-lite-1.0/simpleapi/include -I/fuzz/src/ext/prometheus-cpp-lite-1.0/3rdparty/http-client-lite/include" \
    -S /fuzz/src \
    -B /fuzz/build && \
    cmake --build /fuzz/build -j

# Install headers and library into /fuzz/install
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp /fuzz/build/libzerotiercore.a /fuzz/install/lib/ && \
    cp -r /fuzz/src/include/*.h /fuzz/install/include/
