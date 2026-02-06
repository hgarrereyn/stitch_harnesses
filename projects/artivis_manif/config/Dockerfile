ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies and build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make \
    libeigen3-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and install header-only library
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_TESTING=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_BENCHMARKING=OFF \
    -DBUILD_PYTHON_BINDINGS=OFF \
    -DUSE_SYSTEM_WIDE_TL_OPTIONAL=OFF \
 && cmake --build /fuzz/build --target install -- -v
