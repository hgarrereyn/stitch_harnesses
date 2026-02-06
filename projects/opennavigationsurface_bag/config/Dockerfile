ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for BAG: HDF5, LibXml2, zlib, and build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    make \
    ninja-build \
    pkg-config \
    libhdf5-dev \
    libxml2-dev \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and build BAG
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /build
RUN cmake -G Ninja \
    -DBAG_BUILD_SHARED_LIBS=OFF \
    -DBAG_BUILD_BAG_LIB=ON \
    -DBAG_BUILD_PYTHON=OFF \
    -DBAG_BUILD_TESTS=OFF \
    -DBAG_BUILD_EXAMPLES=OFF \
    -DBAG_BUILD_DOCS=OFF \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    /fuzz/src \
 && cmake --build . --target install -- -v
