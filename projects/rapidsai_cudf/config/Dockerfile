ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# cuDF requires the CUDA toolkit and many GPU dependencies to build. In this
# environment we only need headers to compile fuzz targets against the API types.
# Install step: copy public headers into the install prefix.

RUN set -eux; \
    mkdir -p /fuzz/install/include; \
    cp -r /fuzz/src/cpp/include/* /fuzz/install/include/
