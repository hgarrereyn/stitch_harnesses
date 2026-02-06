ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure and build MetaCall with minimal features
WORKDIR /fuzz/src

RUN cmake -S . -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DOPTION_BUILD_TESTS=OFF \
    -DOPTION_BUILD_BENCHMARKS=OFF \
    -DOPTION_BUILD_DOCS=OFF \
    -DOPTION_BUILD_EXAMPLES=OFF \
    -DOPTION_BUILD_CLI=OFF \
    -DOPTION_BUILD_LOADERS=OFF \
    -DOPTION_BUILD_EXTENSIONS=OFF \
    -DOPTION_BUILD_SCRIPTS=OFF \
    -DOPTION_GIT_HOOKS=OFF \
 && cmake --build /fuzz/build --target install --parallel
