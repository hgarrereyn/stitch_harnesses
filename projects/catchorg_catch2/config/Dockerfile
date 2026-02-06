ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install Catch2 v3 from the provided source in /fuzz/src
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Install minimal build tools (cmake, make)
RUN apt-get update && \
    apt-get install -y --no-install-recommends cmake make ninja-build pkg-config && \
    rm -rf /var/lib/apt/lists/*

# Configure, build, and install as static libraries into /fuzz/install
RUN cmake -S /fuzz/src -B /fuzz/build \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DCATCH_INSTALL_DOCS=OFF \
      -DCATCH_INSTALL_EXTRAS=OFF \
  && cmake --build /fuzz/build -j \
  && cmake --install /fuzz/build
