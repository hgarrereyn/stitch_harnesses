ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        cmake ninja-build make zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure and build deal.II with static library, minimal components, and bundled deps
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DDEAL_II_COMPONENT_EXAMPLES=OFF \
    -DDEAL_II_COMPONENT_DOCUMENTATION=OFF \
    -DDEAL_II_COMPONENT_PYTHON_BINDINGS=OFF \
    -DDEAL_II_ALLOW_BUNDLED=ON \
    -DDEAL_II_FORCE_AUTODETECTION=ON \
    -DDEAL_II_UNITY_BUILD=ON \
    /fuzz/src \
 && cmake --build /fuzz/build --target install -j"$(nproc)"
