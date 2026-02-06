ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN set -eux; \
    export DEBIAN_FRONTEND=noninteractive; \
    apt-get update; \
    apt-get install -y --no-install-recommends ca-certificates pkg-config cmake make; \
    rm -rf /var/lib/apt/lists/*;

WORKDIR /fuzz/src

# Configure and build
RUN set -eux; \
    mkdir -p build && cd build; \
    cmake -G "Unix Makefiles" \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DBUILD_SHARED_LIBS=OFF \
      -DBUILD_STATIC_LIBS=ON \
      -DINSTALL_STATIC_LIBS=ON \
      -DBUILD_TESTING=OFF \
      -DBUILD_TOOLS=OFF \
      -DBUILD_EXAMPLES=OFF \
      -DENABLE_SSL_SUPPORT=OFF \
      ..; \
    cmake --build . --target install -j"$(nproc)";
