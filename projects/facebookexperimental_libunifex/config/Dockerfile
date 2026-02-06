ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends cmake ninja-build pkg-config && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

RUN cmake -G Ninja -S . -B build \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTING=OFF \
    -DUNIFEX_BUILD_EXAMPLES=OFF \
    -DUNIFEX_NO_LIBURING=ON

RUN cmake --build build --target install -- -v
