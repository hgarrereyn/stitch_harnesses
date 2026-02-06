ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and download dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    git curl ca-certificates unzip xz-utils pkg-config build-essential \
    cmake ninja-build \
    && rm -rf /var/lib/apt/lists/*

# Configure and build sherpa-onnx as a static library, install to /fuzz/install
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DSHERPA_ONNX_ENABLE_BINARY=OFF \
    -DSHERPA_ONNX_ENABLE_TTS=OFF \
    -DSHERPA_ONNX_ENABLE_WEBSOCKET=OFF \
    -DSHERPA_ONNX_ENABLE_SPEAKER_DIARIZATION=OFF \
    -DSHERPA_ONNX_ENABLE_PYTHON=OFF \
    -DSHERPA_ONNX_USE_PRE_INSTALLED_ONNXRUNTIME_IF_AVAILABLE=OFF \
    && cmake --build /fuzz/build --target install -j$(nproc)
