ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake make pkg-config \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /fuzz/build /fuzz/install
WORKDIR /fuzz/build
RUN cmake -S /fuzz/src -B . \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTING=OFF \
    -DCMARK_LIB_FUZZER=OFF \
    -DCMAKE_BUILD_TYPE=Release \
 && cmake --build . --config Release -j \
 && cmake --install . --config Release
