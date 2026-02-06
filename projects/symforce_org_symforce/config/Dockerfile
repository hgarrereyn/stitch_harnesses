ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    cmake \
    ninja-build \
    make \
    python3 \
    python3-pip \
    libeigen3-dev \
    libfmt-dev \
    libspdlog-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/* && \
    python3 -m pip install --no-cache-dir --upgrade pip && \
    python3 -m pip install --no-cache-dir argh ply jinja2 && \
    mkdir -p /fuzz/install/include && cp -r /usr/include/eigen3 /fuzz/install/include/

# Configure, build, and install SymForce (C++ only)
WORKDIR /fuzz/src
RUN cmake -S . -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DSYMFORCE_BUILD_STATIC_LIBRARIES=ON \
    -DSYMFORCE_BUILD_EXAMPLES=OFF \
    -DSYMFORCE_BUILD_TESTS=OFF \
    -DSYMFORCE_ADD_PYTHON_TESTS=OFF \
    -DSYMFORCE_BUILD_CC_SYM=OFF \
    -DSYMFORCE_GENERATE_MANIFEST=OFF \
    -DSYMFORCE_BUILD_SYMENGINE=OFF \
    && cmake --build /fuzz/build --target install -j
