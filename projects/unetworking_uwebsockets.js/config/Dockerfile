ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No external dependencies required for our minimal static library build

# Build and install a minimal static library and headers into /fuzz/install
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp /fuzz/src/src/FastTimers.h /fuzz/install/include/FastTimers.h && \
    echo 'extern "C" void uwsjs_dummy(){}' > /tmp/dummy.cpp && \
    stitch_libafl_cxx -c -O2 -fPIC /tmp/dummy.cpp -o /tmp/dummy.o && \
    ar rcs /fuzz/install/lib/libuwebsocketsjs.a /tmp/dummy.o && \
    rm -f /tmp/dummy.cpp /tmp/dummy.o
