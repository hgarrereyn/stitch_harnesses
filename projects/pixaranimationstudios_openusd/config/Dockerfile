ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build dependencies and tools, including newer CMake from Kitware APT
RUN set -eux; \
    apt-get update; \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      gpg ca-certificates wget; \
    wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc | gpg --dearmor -o /usr/share/keyrings/kitware-archive-keyring.gpg; \
    echo "deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main" > /etc/apt/sources.list.d/kitware.list; \
    apt-get update; \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake \
      ninja-build \
      make \
      pkg-config \
      libtbb-dev \
      zlib1g-dev; \
    rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Configure, build only needed targets (tf, arch), and manually install minimal artifacts
RUN set -eux; \
    cmake -G Ninja \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DPXR_ENABLE_PYTHON_SUPPORT=OFF \
      -DPXR_BUILD_IMAGING=OFF \
      -DPXR_BUILD_USD_IMAGING=OFF \
      -DPXR_BUILD_USDVIEW=OFF \
      -DPXR_BUILD_TESTS=OFF \
      -DPXR_BUILD_EXAMPLES=OFF \
      -DPXR_BUILD_TUTORIALS=OFF \
      -DPXR_BUILD_USD_TOOLS=OFF \
      -DPXR_ENABLE_GL_SUPPORT=OFF \
      /fuzz/src; \
    cmake --build . --target tf_headerfiles arch_headerfiles tf arch -j"$(nproc)"; \
    mkdir -p /fuzz/install/include /fuzz/install/lib; \
    # Install headers generated into build tree
    if [ -d "/fuzz/build/include" ]; then cp -a /fuzz/build/include/* /fuzz/install/include/; fi; \
    if [ -d "/fuzz/build/usr/local/include" ]; then cp -a /fuzz/build/usr/local/include/* /fuzz/install/include/; fi; \
    # Copy static libraries for tf and arch
    tf_lib=$(find /fuzz/build -type f -name 'lib*tf.a' | head -n1); \
    arch_lib=$(find /fuzz/build -type f -name 'lib*arch.a' | head -n1); \
    cp -a "$tf_lib" /fuzz/install/lib/; \
    cp -a "$arch_lib" /fuzz/install/lib/; \
    cd /fuzz/install/lib; \
    # Create compatibility symlinks so -lusd_tf/-lusd_arch work regardless of prefix
    if [ ! -f libusd_tf.a ] && [ -f libtf.a ]; then ln -s libtf.a libusd_tf.a; fi; \
    if [ ! -f libusd_arch.a ] && [ -f libarch.a ]; then ln -s libarch.a libusd_arch.a; fi
