ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install libzmq (ZeroMQ) statically into /fuzz/install
ENV DEBIAN_FRONTEND=noninteractive

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure with cmake, using the provided clang wrappers
RUN cmake -S . -B /fuzz/build \
    -G "Ninja" \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED=OFF \
    -DBUILD_STATIC=ON \
    -DENABLE_DRAFTS=OFF \
    -DENABLE_WS=OFF \
    -DWITH_DOCS=OFF \
    -DWITH_LIBBSD=OFF \
    -DWITH_OPENPGM=OFF \
    -DWITH_NORM=OFF \
    -DWITH_VMCI=OFF \
    -DENABLE_CURVE=OFF \
    -DWITH_LIBSODIUM=OFF

RUN cmake --build /fuzz/build --target install -j$(nproc)
