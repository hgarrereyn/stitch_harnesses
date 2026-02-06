ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Build MITIE statically and install headers/libs into /fuzz/install
WORKDIR /fuzz/src/mitielib

# Configure
RUN mkdir -p build && cd build \
 && cmake -G Ninja .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx

# Build
RUN cmake --build build --config Release

# Install: copy library and headers into /fuzz/install
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp -r /fuzz/src/mitielib/include/* /fuzz/install/include/ \
 && cp -r /fuzz/src/dlib/dlib /fuzz/install/include/dlib \
 && LIB_MITIE=$(find build -name "libmitie.a" -print -quit) \
 && LIB_DLIB=$(find build -name "libdlib.a" -print -quit) \
 && cp "$LIB_MITIE" /fuzz/install/lib/ \
 && cp "$LIB_DLIB" /fuzz/install/lib/
