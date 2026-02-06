ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (ensure cmake and ninja are present) and minimal deps
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates cmake ninja-build make \
 && rm -rf /var/lib/apt/lists/*

# Build only the decoder library statically and install headers/libs
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/build
RUN cmake -G Ninja /fuzz/src \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install
# Build only the decoder static lib to keep image small and build fast
RUN cmake --build . --target libhevcdec -- -j$(nproc)

# Manually install since upstream has no install rules
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp -v libhevcdec.a /fuzz/install/lib/ || cp -v */libhevcdec.a /fuzz/install/lib/ \
 && cp -v /fuzz/src/common/iv.h /fuzz/install/include/ \
 && cp -v /fuzz/src/common/ivd.h /fuzz/install/include/ \
 && cp -v /fuzz/src/common/ihevc_typedefs.h /fuzz/install/include/
