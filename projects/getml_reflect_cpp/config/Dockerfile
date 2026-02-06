ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Install newer CMake from Kitware APT and Ninja
RUN apt-get update && apt-get install -y --no-install-recommends \
    wget ca-certificates gnupg \
 && wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc | gpg --dearmor -o /usr/share/keyrings/kitware-archive-keyring.gpg \
 && echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main' > /etc/apt/sources.list.d/kitware.list \
 && apt-get update \
 && apt-get install -y --no-install-recommends cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Configure and build with CMake (static lib, install to /fuzz/install)
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DREFLECTCPP_BUILD_SHARED=OFF \
    -DREFLECTCPP_INSTALL=ON \
    -DREFLECTCPP_USE_BUNDLED_DEPENDENCIES=ON \
    -DREFLECTCPP_ALL_FORMATS=OFF \
    -DREFLECTCPP_JSON=ON \
 && cmake --build build -j \
 && cmake --install build
