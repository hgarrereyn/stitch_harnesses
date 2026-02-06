ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools and recent CMake (>=3.26)
RUN set -eux; \
    apt-get update; \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        ca-certificates \
        gnupg \
        wget; \
    rm -rf /var/lib/apt/lists/*; \
    . /etc/os-release; \
    echo "deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ ${VERSION_CODENAME} main" | tee /etc/apt/sources.list.d/kitware.list >/dev/null; \
    wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc | gpg --dearmor -o /usr/share/keyrings/kitware-archive-keyring.gpg; \
    apt-get update; \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        ninja-build \
        pkg-config; \
    rm -rf /var/lib/apt/lists/*

# Build and install only Poco Foundation as a static library
RUN set -eux; \
    mkdir -p /fuzz/build /fuzz/install && \
    cd /fuzz/build && \
    cmake /fuzz/src \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DPOCO_MINIMAL_BUILD=ON \
      -DENABLE_FOUNDATION=ON \
      -DENABLE_TESTS=OFF \
      -DENABLE_SAMPLES=OFF \
      -G Ninja && \
    cmake --build . --target install -j$(nproc)
