ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies: capnproto headers for kj (used by header-only utilities)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libcapnp-dev \
 && rm -rf /var/lib/apt/lists/*

# "Install" header-only parts of workerd we want to expose for fuzzing
# Use the requested compilers for any build steps (not strictly needed for header copy)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Install headers into /fuzz/install/include
RUN mkdir -p /fuzz/install/include/workerd/util && \
    cp -v /fuzz/src/src/workerd/util/*.h /fuzz/install/include/workerd/util/ || true

# Create lib directory even if we don't build any libs (header-only usage)
RUN mkdir -p /fuzz/install/lib
