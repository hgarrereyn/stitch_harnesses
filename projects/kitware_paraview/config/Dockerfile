ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    libssl-dev \
    zlib1g-dev \
    libexpat1-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure and build ParaView (CORE, no GUI/Python/MPI), static libs
WORKDIR /fuzz/build
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN cmake -G Ninja /fuzz/src \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_BUILD_TYPE=Release \
    -DPARAVIEW_BUILD_SHARED_LIBS=OFF \
    -DPARAVIEW_USE_QT=OFF \
    -DPARAVIEW_USE_PYTHON=OFF \
    -DPARAVIEW_USE_MPI=OFF \
    -DPARAVIEW_ENABLE_RAYTRACING=OFF \
    -DPARAVIEW_BUILD_EDITION=CORE
RUN cmake --build . --target install -- -j$(nproc)
