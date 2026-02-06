ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    clang-17 llvm-17-dev libclang-17-dev zlib1g-dev libncurses5-dev ca-certificates cmake ninja-build \
 && ln -s /usr/bin/clang-17 /usr/local/bin/clang \
 && rm -rf /var/lib/apt/lists/*

# Configure and build ccls
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DUSE_SYSTEM_RAPIDJSON=OFF \
 && cmake --build /fuzz/build --target install

# Install headers for external use
RUN mkdir -p /fuzz/install/include/ccls \
 && cp /fuzz/src/src/*.hh /fuzz/install/include/ccls/ \
 && cp /fuzz/src/src/enum.inc /fuzz/install/include/ccls/ \
 && cp /fuzz/src/third_party/macro_map.h /fuzz/install/include/ \
 && cp -r /fuzz/src/third_party/rapidjson/include/* /fuzz/install/include/
