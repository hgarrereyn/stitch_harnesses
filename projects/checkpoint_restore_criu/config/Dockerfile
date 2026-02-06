ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies to build libcriu (protobuf-c) and basic build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    protobuf-c-compiler \
    libprotobuf-c-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Generate version header only (avoid building whole project)
RUN make -j1 criu/include/version.h

# Generate protobuf-c sources for RPC API
RUN mkdir -p lib/c/images && \
    protoc-c --c_out=lib/c/images --proto_path=images images/rpc.proto

# Build a minimal static libcriu.a from the C bindings and generated RPC stubs
RUN $CC -fPIC -fno-stack-protector -iquote criu/include -iquote lib/c/images -iquote images -c lib/c/criu.c -o /tmp/criu.o && \
    $CC -fPIC -fno-stack-protector -Iimages -c lib/c/images/rpc.pb-c.c -o /tmp/rpc.pb-c.o && \
    mkdir -p /fuzz/install/lib /fuzz/install/include/criu && \
    ar rcs /fuzz/install/lib/libcriu.a /tmp/criu.o /tmp/rpc.pb-c.o && \
    cp -v lib/c/criu.h /fuzz/install/include/criu/ && \
    cp -v criu/include/version.h /fuzz/install/include/criu/ && \
    cp -v lib/c/images/rpc.pb-c.h /fuzz/install/include/criu/
