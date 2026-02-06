ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install Abseil (shared libs to simplify linking)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/src
RUN cmake -S . -B /fuzz/build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DABSL_ENABLE_INSTALL=ON \
    -DBUILD_SHARED_LIBS=ON \
    -DABSL_BUILD_TESTING=OFF \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON
RUN cmake --build /fuzz/build --target install
