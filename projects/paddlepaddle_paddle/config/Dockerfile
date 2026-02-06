ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build deps
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates git build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Prepare install prefix
RUN mkdir -p /fuzz/install/include/paddle/fluid/inference/api \
    /fuzz/install/include/paddle/fluid/inference/capi_exp \
    /fuzz/install/include/paddle/common \
    /fuzz/install/lib

# Copy public headers from source tree
RUN cp -r /fuzz/src/paddle/fluid/inference/api/* /fuzz/install/include/paddle/fluid/inference/api/ || true \
 && cp -r /fuzz/src/paddle/fluid/inference/capi_exp/* /fuzz/install/include/paddle/fluid/inference/capi_exp/ || true \
 && cp -r /fuzz/src/paddle/common/* /fuzz/install/include/paddle/common/ || true

# Provide a minimal stub for missing crypto/cipher.h expected by paddle_api.h
RUN mkdir -p /fuzz/install/include/paddle/fluid/inference/api/crypto \
 && printf "#pragma once\nnamespace framework { class Cipher {}; }\n" > /fuzz/install/include/paddle/fluid/inference/api/crypto/cipher.h

# Create a tiny dummy static library to satisfy linker flags quickly
RUN echo 'void __paddle_infer_dummy(){}' > /tmp/d.c \
 && stitch_libafl_cc -c /tmp/d.c -o /tmp/d.o \
 && ar rcs /fuzz/install/lib/libpaddle_inference.a /tmp/d.o
