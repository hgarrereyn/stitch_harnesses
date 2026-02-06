ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools needed to configure and install the header-only library
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and install to /fuzz/install using the fuzzing compilers
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DDOCTEST_WITH_TESTS=OFF \
    -DDOCTEST_WITH_MAIN_IN_STATIC_LIB=OFF \
 && cmake --build /fuzz/build --target install --parallel
