ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential pkg-config libpng-dev ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Build static library using provided compilers and install artifacts
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

# Build only the static library target
RUN make guetzli_static && \
    mkdir -p /fuzz/install/lib /fuzz/install/include/guetzli /fuzz/install/include/butteraugli && \
    cp -a bin/Release/libguetzli_static.a /fuzz/install/lib/ && \
    cp -a guetzli/*.h /fuzz/install/include/guetzli/ && \
    cp -a third_party/butteraugli/butteraugli/*.h /fuzz/install/include/butteraugli/
