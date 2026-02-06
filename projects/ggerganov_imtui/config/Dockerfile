ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies and build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    git \
    cmake \
    ninja-build \
    make \
    pkg-config \
    libncurses-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Fetch submodules (Dear ImGui) and build/install
WORKDIR /fuzz/src
RUN git submodule update --init --recursive
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DIMTUI_BUILD_EXAMPLES=OFF \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
 && cmake --build build --target install -- -v
