ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    make \
 && rm -rf /var/lib/apt/lists/*

# Use fuzzing compilers
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Build only the lightweight WSON sublibrary (portable C/C++)
RUN cmake -S /fuzz/src/weex_core/Source/wson -B /fuzz/build/wson \
      -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_C_COMPILER=${CC} \
      -DCMAKE_CXX_COMPILER=${CXX} \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
  && cmake --build /fuzz/build/wson -j

# Install headers and library
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
  && cp -r /fuzz/src/weex_core/Source/wson/*.h /fuzz/install/include/ \
  && find /fuzz/build/wson -maxdepth 3 -type f -name 'libwson.*' -exec cp {} /fuzz/install/lib/ \;
