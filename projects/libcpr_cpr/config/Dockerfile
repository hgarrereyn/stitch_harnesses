ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install system curl and build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    libcurl4-openssl-dev \
    ca-certificates \
    pkg-config \
    ninja-build \
    && rm -rf /var/lib/apt/lists/*

# Configure and build cpr using system curl, static library only
RUN cmake -S /fuzz/src -B /tmp/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DCPR_USE_SYSTEM_CURL=ON \
    -DCPR_BUILD_TESTS=OFF \
 && cmake --build /tmp/build --parallel \
 && cmake --install /tmp/build
