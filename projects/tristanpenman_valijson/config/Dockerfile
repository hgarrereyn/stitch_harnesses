ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build deps (cmake may not be present in base)
RUN apt-get update && apt-get install -y --no-install-recommends cmake ninja-build make ca-certificates && rm -rf /var/lib/apt/lists/*

# Configure and install
WORKDIR /fuzz/build
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN cmake -S /fuzz/src -B /fuzz/build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -Dvalijson_BUILD_TESTS=OFF \
    -Dvalijson_BUILD_EXAMPLES=OFF \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
 && cmake --build /fuzz/build --target install -j
