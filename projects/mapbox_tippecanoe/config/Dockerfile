ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends build-essential libsqlite3-dev zlib1g-dev ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

# Build and install binaries
RUN make -j"$(nproc)" PREFIX=/fuzz/install CC=${CC} CXX=${CXX} && make install PREFIX=/fuzz/install

# Create a static library from object files and install headers
RUN mkdir -p /fuzz/install/lib && ar rcs /fuzz/install/lib/libtippecanoe.a *.o jsonpull/*.o && \
    mkdir -p /fuzz/install/include && cp -a *.hpp /fuzz/install/include/ && \
    mkdir -p /fuzz/install/include/jsonpull && cp -a jsonpull/jsonpull.h /fuzz/install/include/jsonpull/
