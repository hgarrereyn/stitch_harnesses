ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies for GTK/WebKitGTK on Ubuntu 22.04
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        pkg-config \
        ninja-build \
        cmake \
        libgtk-3-dev \
        libwebkit2gtk-4.0-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure, build and install webview
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Build both shared and static to simplify linking for consumers
RUN cmake -G Ninja -S /fuzz/src -B build \
      -D CMAKE_BUILD_TYPE=Release \
      -D CMAKE_INSTALL_PREFIX=/fuzz/install \
      -D WEBVIEW_BUILD=ON \
      -D WEBVIEW_BUILD_EXAMPLES=OFF \
      -D WEBVIEW_BUILD_TESTS=OFF \
      -D WEBVIEW_BUILD_DOCS=OFF \
      -D WEBVIEW_ENABLE_CHECKS=OFF \
      -D WEBVIEW_INSTALL_TARGETS=ON \
      -D WEBVIEW_BUILD_SHARED_LIBRARY=ON \
      -D WEBVIEW_BUILD_STATIC_LIBRARY=ON && \
    cmake --build build && \
    cmake --install build
