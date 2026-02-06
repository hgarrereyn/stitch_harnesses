ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config g++ \
    protobuf-compiler libprotobuf-dev \
    libutempter-dev zlib1g-dev libncurses5-dev \
    libssl-dev ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Use the fuzzer compiler wrappers
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Generate build system, configure, build, and install
RUN ./autogen.sh && \
    ./configure --prefix=/fuzz/install && \
    make -j"$(nproc)" && \
    make install

# Manually install static libraries and headers (not installed by default)
RUN mkdir -p /fuzz/install/lib && \
    find src -maxdepth 2 -type f -name "*.a" -exec cp -v {} /fuzz/install/lib/ \; && \
    mkdir -p /fuzz/install/include/src/crypto \
             /fuzz/install/include/src/network \
             /fuzz/install/include/src/statesync \
             /fuzz/install/include/src/terminal \
             /fuzz/install/include/src/util \
             /fuzz/install/include/src/protobufs \
             /fuzz/install/include/src/include && \
    cp -v src/include/config.h /fuzz/install/include/src/include/ && \
    cp -v src/crypto/*.h /fuzz/install/include/src/crypto/ && \
    cp -v src/network/*.h /fuzz/install/include/src/network/ && \
    cp -v src/statesync/*.h /fuzz/install/include/src/statesync/ && \
    cp -v src/terminal/*.h /fuzz/install/include/src/terminal/ && \
    cp -v src/util/*.h /fuzz/install/include/src/util/ && \
    # protobuf headers are generated during build
    cp -v src/protobufs/*.pb.h /fuzz/install/include/src/protobufs/ || true
