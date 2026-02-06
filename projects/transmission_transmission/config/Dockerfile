ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    pkg-config \
    cmake \
    make \
    ninja-build \
    libssl-dev \
    libcurl4-openssl-dev \
    zlib1g-dev \
    gettext \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libtransmission only
WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DENABLE_DAEMON=OFF \
    -DENABLE_GTK=OFF \
    -DENABLE_QT=OFF \
    -DENABLE_UTILS=OFF \
    -DENABLE_CLI=OFF \
    -DENABLE_TESTS=OFF \
    -DENABLE_NLS=OFF \
    -DINSTALL_DOC=OFF \
    -DINSTALL_WEB=OFF \
    -DINSTALL_LIB=ON \
    -DUSE_SYSTEM_DEFAULT=OFF \
    -DWITH_CRYPTO=openssl \
  && cmake --build build -j$(nproc) \
  && cmake --install build

# Also install all third-party static libs into /fuzz/install/lib, merge into a single archive,
# and copy any header-only third-party includes into /fuzz/install/include
RUN set -eux; \
    mkdir -p /fuzz/install/lib /tmp/merge && cd /tmp/merge; \
    find /fuzz/src/build -type f -name '*.a' -print0 | xargs -0 -I{} ar x {}; \
    ar rcs /fuzz/install/lib/libtransmission_all.a *.o || true; \
    rm -rf /tmp/merge; \
    # Make libtransmission headers resolve, and add any missing internal headers needed by public API
    ln -sfn /fuzz/install/include/transmission /fuzz/install/include/libtransmission; \
    cp /fuzz/src/libtransmission/net.h /fuzz/install/include/libtransmission/; \
    for d in /fuzz/src/third-party/*; do \
      if [ -d "$d/include" ]; then cp -r "$d/include/." /fuzz/install/include/; fi; \
      if [ -d "$d/source" ]; then cp -r "$d/source/." /fuzz/install/include/; fi; \
    done; \
    if [ -d /fuzz/src/build/third-party ]; then \
      for d in /fuzz/src/build/third-party/*; do \
        if [ -d "$d/include" ]; then cp -r "$d/include/." /fuzz/install/include/; fi; \
      done; \
    fi
