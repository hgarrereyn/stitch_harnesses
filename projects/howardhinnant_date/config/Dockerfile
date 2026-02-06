ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
    libcurl4-openssl-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install (static) with CMake
WORKDIR /fuzz/src
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_TZ_LIB=ON \
    -DBUILD_SHARED_LIBS=OFF \
    -DENABLE_DATE_INSTALL=ON \
    -DUSE_SYSTEM_TZ_DB=OFF \
    -DMANUAL_TZ_DB=OFF \
 && cmake --build build --target install -j
