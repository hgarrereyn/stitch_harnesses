ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools and dev headers needed by public headers
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates build-essential cmake ninja-build \
    libgoogle-glog-dev libgflags-dev \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# "Install" headers only to keep image light for fuzzing builds
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -a include/*.h /fuzz/install/include/ \
 && mkdir -p /fuzz/install/include/net/include /fuzz/install/include/pstd/include /fuzz/install/include/storage /fuzz/install/include/src/cache/include \
 && cp -a src/net/include/*.h /fuzz/install/include/net/include/ \
 && cp -a src/pstd/include/*.h /fuzz/install/include/pstd/include/ \
 && cp -a src/storage/include/storage/*.h /fuzz/install/include/storage/ \
 && cp -a src/cache/include/*.h /fuzz/install/include/src/cache/include/
