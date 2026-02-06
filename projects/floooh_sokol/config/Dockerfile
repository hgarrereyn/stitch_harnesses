ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal dependencies
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

# "Install" header-only library by copying headers into /fuzz/install/include
RUN mkdir -p /fuzz/install/include && \
    cp -v /fuzz/src/*.h /fuzz/install/include/ && \
    mkdir -p /fuzz/install/include/util && \
    cp -v /fuzz/src/util/*.h /fuzz/install/include/util/

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
ENV CFLAGS="" CXXFLAGS="" LDFLAGS=""

# Nothing to build; headers are installed above
