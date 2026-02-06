ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends binutils ca-certificates && rm -rf /var/lib/apt/lists/*

# Build BearSSL static library
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc
# Build with default Unix configuration, using our compiler wrapper
RUN make -j"$(nproc)" CONF=Unix

# Install headers and static library into /fuzz/install
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
    && cp -a inc/*.h /fuzz/install/include/ \
    && cp -a build/libbearssl.a /fuzz/install/lib/
