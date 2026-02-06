ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (cmake, make, flex and bison for scanner/parser generation)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    make \
    flex \
    bison \
 && rm -rf /var/lib/apt/lists/*

# Configure and build libcue as a static library, install to /fuzz/install
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G "Unix Makefiles" \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DBUILD_SHARED_LIBS=OFF \
 && cmake --build /fuzz/build --target install -j"$(nproc)"
