ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && \
    apt-get install -y --no-install-recommends cmake ninja-build pkg-config && \
    rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz

RUN cmake -S /fuzz/src -B /fuzz/build \
      -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DBUILD_SHARED_LIBS=OFF \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DCMAKE_C_COMPILER=${CC} \
      -DCMAKE_CXX_COMPILER=${CXX} \
      -DHB_BUILD_UTILS=OFF \
      -DHB_HAVE_GOBJECT=OFF \
      -DHB_HAVE_ICU=OFF \
      -DHB_HAVE_GLIB=OFF \
      -DHB_HAVE_FREETYPE=OFF \
      -DHB_HAVE_GRAPHITE2=OFF \
      -DHB_HAVE_CAIRO=OFF \
  && cmake --build /fuzz/build --target install -j$(nproc)
