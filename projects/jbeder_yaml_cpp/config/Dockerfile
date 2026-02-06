ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal extra tools (cmake might not be present in base image)
RUN apt-get update && apt-get install -y --no-install-recommends cmake ninja-build && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Configure, build, and install yaml-cpp as a static library
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DYAML_BUILD_SHARED_LIBS=OFF \
    -DYAML_CPP_BUILD_TESTS=OFF \
    -DYAML_CPP_BUILD_TOOLS=OFF \
    && cmake --build build --target install
