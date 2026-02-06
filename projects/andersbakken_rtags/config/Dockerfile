ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies: git for submodules, libclang/llvm for headers and llvm-config,
# plus common libs rct may use (zlib, ssl)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    git \
    ninja-build \
    llvm-14-dev \
    libclang-14-dev \
    zlib1g-dev \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Fetch submodules (rct)
WORKDIR /fuzz/src
RUN git submodule update --init --recursive || true

# Configure and build
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DRTAGS_NO_ELISP_FILES=ON \
    -DSKIP_CTEST=ON \
    && cmake --build /fuzz/build --target rtags rc rdm rp -- -v \
    && cmake --install /fuzz/build || true

# Manually install static libs and headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include /fuzz/install/include/rct \
    && set -eux; \
    find /fuzz/build -name "librtags*.a" -exec cp -v {} /fuzz/install/lib/ \; \
    && find /fuzz/build -name "librct*.a" -exec cp -v {} /fuzz/install/lib/ \; \
    || true

# Install headers: project headers and generated headers
RUN set -eux; \
    cp -v /fuzz/src/src/*.h /fuzz/install/include/ || true; \
    [ -d /fuzz/build/src/include ] && cp -vr /fuzz/build/src/include/* /fuzz/install/include/ || true; \
    # rct headers from submodule: copy everything to a catch-all include root
    if [ -d /fuzz/src/src/rct ]; then \
      mkdir -p /fuzz/install/include/rct-all; \
      cp -vr /fuzz/src/src/rct/* /fuzz/install/include/rct-all/ || true; \
    fi; \
    # generated rct-config.h
    find /fuzz/build -name rct-config.h -exec cp -v {} /fuzz/install/include/rct/rct-config.h \; || true; \
    # ensure it exists for header consumption
    [ -f /fuzz/install/include/rct/rct-config.h ] || echo "/* generated placeholder */" > /fuzz/install/include/rct/rct-config.h
