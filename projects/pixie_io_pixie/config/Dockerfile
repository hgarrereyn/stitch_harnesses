ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install header dependencies (glog/gflags for logging.h)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    libgflags-dev \
    libgoogle-glog-dev \
 && rm -rf /var/lib/apt/lists/*

# Set compilers and install prefix
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

# "Build and install": copy the needed headers into the install prefix from /fuzz/src.
RUN mkdir -p ${INSTALL_PREFIX}/include/src/common/base \
 && cp -r /fuzz/src/src/common/base/* ${INSTALL_PREFIX}/include/src/common/base/

