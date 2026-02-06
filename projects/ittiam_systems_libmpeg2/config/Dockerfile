ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any extra build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
 && rm -rf /var/lib/apt/lists/*

# Use fuzzer compiler wrappers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Configure
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install

# Build only the library target
RUN cmake --build /fuzz/build --target libmpeg2dec -j

# Install: copy library and public headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp /fuzz/build/libmpeg2dec.a /fuzz/install/lib/ \
 && cp /fuzz/src/common/iv_datatypedef.h /fuzz/install/include/ \
 && cp /fuzz/src/common/iv.h /fuzz/install/include/ \
 && cp /fuzz/src/decoder/ivd.h /fuzz/install/include/ \
 && cp /fuzz/src/decoder/impeg2d.h /fuzz/install/include/ \
 && cp /fuzz/src/decoder/impeg2d_api.h /fuzz/install/include/
