ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Set compilers to the required wrappers
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Install a minimal subset of headers and a stub static library to link against
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp /fuzz/src/dev/Common/Microsoft.TraceLogging.h /fuzz/install/include/ && \
    echo "void __windowsappsdk_stub(void){}" > /tmp/stub.c && \
    ${CC} -c /tmp/stub.c -o /tmp/stub.o && \
    ar rcs /fuzz/install/lib/libwindowsappsdk.a /tmp/stub.o && \
    rm -f /tmp/stub.c /tmp/stub.o
