ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libabsl-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp -r quiche /fuzz/install/include/ && \
    "$CXX" -O2 -fPIC -I/fuzz/src -I/fuzz/src/quiche/common/platform/default \
      -c quiche/common/simple_buffer_allocator.cc -o /tmp/simple_buffer_allocator.o && \
    ar rcs /fuzz/install/lib/libquiche_core.a /tmp/simple_buffer_allocator.o && \
    rm -f /tmp/simple_buffer_allocator.o
