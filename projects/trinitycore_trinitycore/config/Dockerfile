ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    gnupg \
    wget \
    ninja-build \
    pkg-config \
    python3 \
    libboost-all-dev \
    libreadline-dev \
    libmysqlclient-dev \
    zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

# Add Kitware APT repo for newer CMake (>=3.24 required)
RUN set -eux; \
    wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc | gpg --dearmor -o /usr/share/keyrings/kitware-archive-keyring.gpg; \
    echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main' > /etc/apt/sources.list.d/kitware.list; \
    apt-get update; \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends cmake; \
    rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DWITH_WARNINGS_AS_ERRORS=OFF \
    -DWITH_SOURCE_TREE=hierarchical-folders

# Build only the common static library
RUN cmake --build build --target common -j$(nproc)

# Install: copy static lib and selected public headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
    && cp build/src/common/libcommon.a /fuzz/install/lib/ \
    && cp src/common/Common.h src/common/Define.h src/common/CompilerDefs.h /fuzz/install/include/
