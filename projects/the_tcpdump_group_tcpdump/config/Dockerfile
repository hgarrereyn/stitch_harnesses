ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies and build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
    libpcap-dev \
 && rm -rf /var/lib/apt/lists/*

# Build tcpdump (netdissect static library)
WORKDIR /fuzz/src

# Configure and build with CMake
RUN mkdir -p build && cd build && \
    CC=gf_libafl_cc CXX=gf_libafl_cxx \
    cmake -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      .. && \
    ninja -v

# Install artifacts manually: static lib and headers
RUN set -eux; \
    mkdir -p /fuzz/install/lib /fuzz/install/include; \
    cp build/libnetdissect.a /fuzz/install/lib/; \
    cp -a *.h /fuzz/install/include/; \
    cp build/config.h /fuzz/install/include/
