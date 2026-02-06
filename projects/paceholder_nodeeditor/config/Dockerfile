ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools, Qt6 dev packages, and OpenGL
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake \
      ninja-build \
      pkg-config \
      qt6-base-dev \
      qt6-base-dev-tools \
      libqt6opengl6-dev \
      libgl1-mesa-dev \
      ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, install
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTING=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_DOCS=OFF \
    -DUSE_QT6=ON \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} && \
    cmake --build /fuzz/build --target install -- -v
