ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build \
        -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/fuzz/install \
        -DBUILD_SHARED_LIB=OFF \
        -DSUPPORT_CONSOLE_APP=OFF \
        -DSUPPORT_LOCALIZATIONS=OFF \
    && cmake --build /fuzz/build --target install -j$(nproc)
