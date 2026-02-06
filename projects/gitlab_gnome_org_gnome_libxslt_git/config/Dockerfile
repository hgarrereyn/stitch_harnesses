ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
    libxml2-dev \
 && rm -rf /var/lib/apt/lists/*

# Provide a minimal CMake package config for system libxml2
RUN mkdir -p /usr/lib/x86_64-linux-gnu/cmake/libxml2 \
 && printf "include(CMakeFindDependencyMacro)\nadd_library(LibXml2::LibXml2 INTERFACE IMPORTED)\nset_target_properties(LibXml2::LibXml2 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES \"/usr/include/libxml2\" INTERFACE_LINK_LIBRARIES \"xml2\")\n" \
    > /usr/lib/x86_64-linux-gnu/cmake/libxml2/LibXml2Config.cmake

# Configure, build, and install libxslt statically using CMake
WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DLIBXSLT_WITH_PROGRAMS=OFF \
    -DLIBXSLT_WITH_PYTHON=OFF \
    -DLIBXSLT_WITH_TESTS=OFF \
    -DLIBXSLT_WITH_MODULES=OFF \
    -DLIBXSLT_WITH_CRYPTO=OFF \
 && cmake --build build --target install
