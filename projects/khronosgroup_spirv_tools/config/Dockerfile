ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and fetch third-party deps
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake \
      python3 \
      ninja-build \
      git && \
    rm -rf /var/lib/apt/lists/*

# Sync dependencies (SPIRV-Headers, etc.) into external/
RUN cd /fuzz/src && python3 utils/git-sync-deps

# Configure, build, and install SPIRV-Tools (static libs only)
RUN mkdir -p /fuzz/build && cd /fuzz/build && \
    cmake -G Ninja /fuzz/src \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DSPIRV_SKIP_EXECUTABLES=ON \
      -DSPIRV_SKIP_TESTS=ON \
      -DSPIRV_TOOLS_BUILD_STATIC=ON \
      -DSPIRV_WERROR=OFF && \
    cmake --build . --target install -- -v
