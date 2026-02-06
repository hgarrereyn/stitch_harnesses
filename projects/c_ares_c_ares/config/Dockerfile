ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends cmake ninja-build make ca-certificates pkg-config && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN cmake -S . -B build -G Ninja \
    -DCARES_STATIC=ON -DCARES_SHARED=OFF \
    -DCARES_BUILD_TOOLS=OFF \
    -DCARES_STATIC_PIC=ON \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
  && cmake --build build --target install
