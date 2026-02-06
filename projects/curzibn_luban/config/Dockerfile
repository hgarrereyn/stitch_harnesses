ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libturbojpeg0-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# "Build and install" the target: expose turbojpeg.h from the project and a tiny stub static lib
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Install headers
RUN mkdir -p /fuzz/install/include && \
    cp /fuzz/src/luban/src/main/cpp/turbojpeg.h /fuzz/install/include/

# Build and install a tiny static library so linkers have a project lib to link against
RUN mkdir -p /tmp/build && cd /tmp/build && \
    printf "%s\n" "int luban_stub_version(void){return 1;}" > stub.c && \
    ${CC} -c stub.c -o stub.o && \
    ar rcs libluban_stub.a stub.o && \
    mkdir -p /fuzz/install/lib && \
    cp libluban_stub.a /fuzz/install/lib && \
    rm -rf /tmp/build
