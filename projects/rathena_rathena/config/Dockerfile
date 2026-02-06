ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for building rAthena (system MySQL client, zlib, libconfig, cmake)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    ninja-build \
    pkg-config \
    cmake \
    default-libmysqlclient-dev \
    zlib1g-dev \
    libconfig-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure & build
RUN cmake -S /fuzz/src -B /fuzz/build \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SERVERS=OFF \
 && cmake --build /fuzz/build -j

# Install-like step: copy built static libs and headers to /fuzz/install
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/common /fuzz/install/include/config /fuzz/install/include/custom \
 && if [ -d /fuzz/src/lib ]; then cp -a /fuzz/src/lib/*.a /fuzz/install/lib/ || true; fi \
 && if [ -d /fuzz/build/lib ]; then cp -a /fuzz/build/lib/*.a /fuzz/install/lib/ || true; fi \
 && cp -a /fuzz/src/src/common/*.hpp /fuzz/install/include/common/ \
 && cp -a /fuzz/src/src/config/* /fuzz/install/include/config/ \
 && cp -a /fuzz/src/src/custom/* /fuzz/install/include/custom/ \
 && if [ -f /fuzz/build/src/common/version.hpp ]; then cp /fuzz/build/src/common/version.hpp /fuzz/install/include/common/; fi \
 && cp -a /fuzz/src/3rdparty/rapidyaml/src/* /fuzz/install/include/ \
 && cp -a /fuzz/src/3rdparty/rapidyaml/ext/c4core/src/* /fuzz/install/include/ \
 && cd /fuzz/install/lib \
 && for n in minicore common common_base yaml-cpp ryml c4core; do \
      if [ ! -f lib${n}.a ]; then \
        f=$(ls -1 lib${n}*.a 2>/dev/null | head -n1); \
        if [ -n "$f" ]; then ln -s "$f" lib${n}.a; fi; \
      fi; \
    done
