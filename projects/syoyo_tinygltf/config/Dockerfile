ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools (in case base image is missing them)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
      cmake ninja-build make \
    && rm -rf /var/lib/apt/lists/*

# Build and install TinyGLTF to /fuzz/install
RUN cmake -S /fuzz/src -B /build -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DTINYGLTF_HEADER_ONLY=OFF \
      -DTINYGLTF_INSTALL=ON \
      -DTINYGLTF_INSTALL_VENDOR=ON \
      -DTINYGLTF_BUILD_LOADER_EXAMPLE=OFF \
      -DTINYGLTF_BUILD_GL_EXAMPLES=OFF \
      -DTINYGLTF_BUILD_VALIDATOR_EXAMPLE=OFF \
      -DTINYGLTF_BUILD_BUILDER_EXAMPLE=OFF \
  && cmake --build /build --target install -j \
  && rm -rf /build
