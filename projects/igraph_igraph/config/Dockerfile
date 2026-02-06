ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build \
    && rm -rf /var/lib/apt/lists/*

# Configure and build igraph statically, install into /fuzz/install
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN cmake -S /fuzz/src -B /tmp/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTING=OFF \
    -DIGRAPH_GLPK_SUPPORT=OFF \
    -DIGRAPH_INFOMAP_SUPPORT=OFF \
    -DIGRAPH_GRAPHML_SUPPORT=OFF \
    -DIGRAPH_OPENMP_SUPPORT=OFF && \
    cmake --build /tmp/build --target install -j$(nproc) && \
    rm -rf /tmp/build