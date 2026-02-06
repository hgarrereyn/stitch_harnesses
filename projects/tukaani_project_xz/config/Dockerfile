ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Ensure required build tools are available
RUN apt-get update && apt-get install -y --no-install-recommends \
      cmake ninja-build make pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Build and install static liblzma from the bundled XZ Utils sources
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz

RUN mkdir -p /fuzz/build && \
    cmake -S /fuzz/src -B /fuzz/build -G Ninja \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DCMAKE_BUILD_TYPE=Release \
      -DBUILD_SHARED_LIBS=OFF \
      -DXZ_NLS=OFF \
      -DXZ_TOOL_XZ=OFF \
      -DXZ_TOOL_XZDEC=OFF \
      -DXZ_TOOL_LZMADEC=OFF \
      -DXZ_TOOL_LZMAINFO=OFF \
      -DXZ_TOOL_SCRIPTS=OFF && \
    cmake --build /fuzz/build --target install -j"$(nproc)"
