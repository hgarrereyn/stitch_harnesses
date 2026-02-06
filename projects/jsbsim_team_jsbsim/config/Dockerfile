ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build \
  && rm -rf /var/lib/apt/lists/*

# Configure, build, and install JSBSim as a static library
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz/build
RUN cmake -G Ninja \
    -S /fuzz/src \
    -B /fuzz/build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_DOCS=OFF \
    -DBUILD_PYTHON_MODULE=OFF \
    -DBUILD_JULIA_PACKAGE=OFF \
    -DBUILD_MATLAB_SFUNCTION=OFF \
    -DSYSTEM_EXPAT=OFF \
  && cmake --build /fuzz/build --target install -- -v
