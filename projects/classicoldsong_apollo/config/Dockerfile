ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    pkg-config \
    cmake \
    ninja-build \
    make \
    binutils \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DSUNSHINE_CONFIGURE_ONLY=ON

RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp /fuzz/src/src/move_by_copy.h /fuzz/install/include/move_by_copy.h && \
    printf "%s\n" "void apollo_dummy(void){}" > /tmp/dummy.c && \
    gf_libafl_cc -c /tmp/dummy.c -o /tmp/dummy.o && \
    ar rcs /fuzz/install/lib/libapollo.a /tmp/dummy.o && \
    rm -f /tmp/dummy.c /tmp/dummy.o
