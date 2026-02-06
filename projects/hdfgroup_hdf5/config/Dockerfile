ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    ninja-build wget ca-certificates gnupg \
 && rm -rf /var/lib/apt/lists/*

# Install modern CMake (>=3.26) from Kitware APT repo
RUN set -eux; \
    mkdir -p /usr/share/keyrings; \
    wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc | gpg --dearmor -o /usr/share/keyrings/kitware-archive-keyring.gpg; \
    echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main' > /etc/apt/sources.list.d/kitware.list; \
    apt-get update; \
    apt-get install -y --no-install-recommends cmake; \
    rm -rf /var/lib/apt/lists/*

# Build HDF5 statically with C, HL and C++ (HL C++ too)
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_STATIC_LIBS=ON \
    -DHDF5_BUILD_TOOLS=OFF \
    -DHDF5_BUILD_EXAMPLES=OFF \
    -DBUILD_TESTING=OFF \
    -DHDF5_ENABLE_ZLIB_SUPPORT=OFF \
    -DHDF5_BUILD_HL_LIB=ON \
    -DHDF5_BUILD_CPP_LIB=ON \
 && cmake --build /fuzz/build --target install -- -v

