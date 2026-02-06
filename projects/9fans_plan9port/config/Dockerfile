ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build plan9port libraries (static) using gf_libafl_cc and install headers/libs
ENV PLAN9=/fuzz/src
WORKDIR /fuzz/src

# Force the build system to use the fuzzing compiler wrapper
RUN printf "CC9=gf_libafl_cc\n" > LOCAL.config \
 && ./INSTALL -b \
 && mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -a include/* /fuzz/install/include/ \
 && cp -a lib/*.a /fuzz/install/lib/

# Nothing else to do; test program will be built later
