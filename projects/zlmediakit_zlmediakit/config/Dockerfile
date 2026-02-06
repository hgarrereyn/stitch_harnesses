ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (cmake/ninja may not be present in minimal base)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure and build C API as shared lib (pulls in static deps)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz
RUN mkdir -p build install
WORKDIR /fuzz/build

RUN cmake -G Ninja \
  -DCMAKE_C_COMPILER=gf_libafl_cc \
  -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
  -DCMAKE_INSTALL_PREFIX=/fuzz/install \
  -DBUILD_SHARED_LIBS=OFF \
  -DENABLE_API=ON \
  -DENABLE_API_STATIC_LIB=OFF \
  -DENABLE_CXX_API=ON \
  -DENABLE_TESTS=OFF \
  -DENABLE_SERVER=OFF \
  -DENABLE_PLAYER=OFF \
  -DENABLE_OPENSSL=OFF \
  -DENABLE_FFMPEG=OFF \
  -DENABLE_WEBRTC=OFF \
  -DENABLE_SRT=OFF \
  -DENABLE_SCTP=OFF \
  /fuzz/src && \
  cmake --build . --target install -- -v
