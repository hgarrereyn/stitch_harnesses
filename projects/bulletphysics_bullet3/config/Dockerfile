ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
 && rm -rf /var/lib/apt/lists/*

# Configure compilers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Configure, build, and install Bullet (static libs, no demos/tests)
WORKDIR /fuzz/src
RUN cmake -S . -B /tmp/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_CPU_DEMOS=OFF \
    -DBUILD_BULLET2_DEMOS=OFF \
    -DBUILD_OPENGL3_DEMOS=OFF \
    -DBUILD_EXTRAS=OFF \
    -DBUILD_UNIT_TESTS=OFF \
    -DINSTALL_LIBS=ON \
    -DBUILD_PYBULLET=OFF
RUN cmake --build /tmp/build --target install -j$(nproc)
