ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Install required build tools (cmake/ninja may not be present in some base images)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Set compilers to fuzzing wrappers
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Configure and install: disable optional extras so no third-party headers are needed
RUN cmake -S /fuzz/src -B /tmp/build \
    -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DUSEARCH_INSTALL=ON \
    -DUSEARCH_USE_FP16LIB=OFF \
    -DUSEARCH_USE_SIMSIMD=OFF \
    -DUSEARCH_BUILD_LIB_C=OFF \
    -DUSEARCH_BUILD_TEST_CPP=OFF \
    -DUSEARCH_BUILD_BENCH_CPP=OFF \
    -DUSEARCH_BUILD_JNI=OFF \
    -DUSEARCH_BUILD_SQLITE=OFF \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx && \
    cmake --build /tmp/build --target install --config Release && \
    rm -rf /tmp/build
