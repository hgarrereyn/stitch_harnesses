ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    git ca-certificates cmake ninja-build make \
  && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/build

RUN cmake -GNinja -S /fuzz/src -B /fuzz/build -DCMAKE_INSTALL_PREFIX=/fuzz/install
RUN cmake --build /fuzz/build --target heap_layers -j || true
RUN cmake --build /fuzz/build --target mesh -j

RUN mkdir -p /fuzz/install/include/plasma /fuzz/install/lib \
 && cp -v /fuzz/src/src/plasma/mesh.h /fuzz/install/include/plasma/ \
 && cp -v /fuzz/src/build/lib/libmesh.so /fuzz/install/lib/
