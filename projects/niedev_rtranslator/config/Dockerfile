ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    ninja-build \
    cmake \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Build and install the vendored SentencePiece library (Android patches removed)
RUN set -eux; \
    cd /fuzz/src/app/src/main/cpp/src; \
    # Drop Android-only linkage against android/log
    sed -i '/^target_link_libraries(\${CMAKE_PROJECT_NAME}/,/^)/d' CMakeLists.txt; \
    # Exclude JNI sources that require Android NDK headers
    sed -i '/CacheContainerNative.cpp/d' CMakeLists.txt; \
    sed -i '/SentencePieceProcessorInterface.cpp/d' CMakeLists.txt; \
    sed -i '/NNAPITest.cpp/d' CMakeLists.txt; \
    mkdir -p /fuzz/build && cd /fuzz/build && \
    cmake -G Ninja /fuzz/src/app/src/main/cpp \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DSPM_ENABLE_SHARED=OFF \
      -DSPM_ABSL_PROVIDER=internal \
      -DSPM_PROTOBUF_PROVIDER=internal \
      -DSPM_BUILD_TEST=OFF \
      -DSPM_ENABLE_TCMALLOC=OFF \
      && \
    cmake --build . --target install
