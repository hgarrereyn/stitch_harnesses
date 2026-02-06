ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools and dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    git ca-certificates cmake ninja-build make pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure and build EASTL statically
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DEASTL_BUILD_TESTS=OFF \
    -DEASTL_BUILD_BENCHMARK=OFF \
    -DCMAKE_CXX_FLAGS="-DEASTL_DLL=1" \
 && cmake --build /fuzz/build --target install

# Copy EABase headers fetched by FetchContent into install include path for downstream consumers
# This ensures headers like <EABase/nullptr.h> are available when including EASTL headers outside of CMake.
RUN if [ -d /fuzz/build/_deps/eabase-src/include ]; then \
      cp -r /fuzz/build/_deps/eabase-src/include/* /fuzz/install/include/; \
    fi
