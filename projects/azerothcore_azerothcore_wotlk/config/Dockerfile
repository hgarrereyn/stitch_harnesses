ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install system dependencies required by the project (MySQL client dev, OpenSSL)
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      default-libmysqlclient-dev \
      libssl-dev \
      ca-certificates \
      ninja-build \
    && rm -rf /var/lib/apt/lists/*

# Configure the project (avoid building heavy apps/tools), and install
# We still configure so CMake generates include paths and checks deps
RUN cmake -S /fuzz/src -B /fuzz/build \
      -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DAPPS_BUILD=none \
      -DTOOLS_BUILD=none && \
    cmake --build /fuzz/build --target install || true

# Manually install headers needed for using the shared public definitions
RUN mkdir -p /fuzz/install/include/acore/shared && \
    mkdir -p /fuzz/install/include/acore/common && \
    cp -r /fuzz/src/src/server/shared/* /fuzz/install/include/acore/shared/ && \
    cp -r /fuzz/src/src/common/* /fuzz/install/include/acore/common/
