ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install necessary build tools (cmake, ninja) in case base image lacks them
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config ca-certificates && \
    rm -rf /var/lib/apt/lists/*

ENV INSTALL_PREFIX=/fuzz/install \
    SRC_DIR=/fuzz/src

# Build Crypto++ static library from subdirectory (independent of IDA SDK)
RUN set -eux; \
    mkdir -p ${INSTALL_PREFIX} && \
    cd ${SRC_DIR}/src/cryptopp-cmake && \
    cmake -S . -B build -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DBUILD_SHARED_LIBS=OFF \
      -DCRYPTOPP_BUILD_TESTING=OFF && \
    cmake --build build --target install

# Install a minimal public header from the project that doesn't require IDA SDK
RUN install -d ${INSTALL_PREFIX}/include && \
    install -m 0644 ${SRC_DIR}/src/ordered_set.h ${INSTALL_PREFIX}/include/
