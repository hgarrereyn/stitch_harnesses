ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Install minimal build tools needed to run CMake configure & install
RUN apt-get update && apt-get install -y --no-install-recommends \
      cmake make \
    && rm -rf /var/lib/apt/lists/*

# Configure and install Taskflow headers to /fuzz/install
RUN cmake -S /fuzz/src -B /tmp/build \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DTF_BUILD_TESTS=OFF \
    -DTF_BUILD_EXAMPLES=OFF \
    -DTF_BUILD_PROFILER=OFF \
    -DTF_BUILD_BENCHMARKS=OFF \
    -DTF_BUILD_CUDA=OFF \
 && cmake --build /tmp/build --target install \
 && rm -rf /tmp/build
