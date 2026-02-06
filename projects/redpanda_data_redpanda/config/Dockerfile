ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install system build dependencies required by Redpanda's Bazel setup
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    ca-certificates \
    curl \
    wget \
    git \
    pkg-config \
    make \
    autoconf \
    automake \
    libtool \
    bison \
    autopoint \
    elfutils \
    && rm -rf /var/lib/apt/lists/*

# Install bazelisk (bazel wrapper)
RUN wget -O /usr/local/bin/bazel https://github.com/bazelbuild/bazelisk/releases/latest/download/bazelisk-linux-amd64 \
    && chmod +x /usr/local/bin/bazel

# Environment
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Build a small target to validate toolchain (not strictly needed for header-only use)
RUN ./bazel/install-deps.sh && \
    bazel build //:BUILD >/dev/null || true

# Install headers for a tiny public component
RUN mkdir -p ${PREFIX}/include/base && \
    cp -v src/v/base/likely.h ${PREFIX}/include/base/
