ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make \
    libboost-all-dev \
    libstdc++-12-dev \
 && rm -rf /var/lib/apt/lists/*

# Build QQ-CTPAPI library
WORKDIR /fuzz/src/QQ-CTPAPI

# Configure with fuzzing compilers and ensure Boost libs are linked on Linux
RUN cmake -S . -B /tmp/build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_SHARED_LINKER_FLAGS="-lboost_system -lboost_thread -lpthread" \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install

# Build
RUN cmake --build /tmp/build --config Release

# Manually install artifacts (CMake project has no install rules)
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp -v /fuzz/src/QQ-CTPAPI/libthostmduserapi_se.* /fuzz/install/lib/ \
 && cp -v /fuzz/src/QQ-CTPAPI/ThostFtdcMdApi.h /fuzz/install/include/ \
 && cp -v /fuzz/src/QQ-CTPAPI/ThostFtdcUserApiStruct.h /fuzz/install/include/ \
 && cp -v /fuzz/src/QQ-CTPAPI/ThostFtdcUserApiDataType.h /fuzz/install/include/
