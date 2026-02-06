ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (cmake and ninja)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build uriparser as a static library
WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DURIPARSER_SHARED_LIBS=OFF \
    -DURIPARSER_BUILD_TESTS=OFF \
    -DURIPARSER_BUILD_DOCS=OFF \
    -DURIPARSER_BUILD_TOOLS=OFF \
    -DURIPARSER_BUILD_FUZZERS=OFF \
    -DURIPARSER_ENABLE_INSTALL=ON \
 && cmake --build /fuzz/build --parallel \
 && cmake --install /fuzz/build
