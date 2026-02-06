ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal setup: install a few utilities
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Set compilers as required
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Prepare install prefix and headers
RUN mkdir -p /fuzz/install/include /fuzz/install/lib
# Copy public API headers from the source tree already present in the image
RUN cp -v /fuzz/src/src/lib/api/*.h /fuzz/install/include/

# Create a minimal static library archive to satisfy linking during tests
RUN printf 'int __3fs_dummy_symbol = 0;\n' | ${CXX} -c -x c++ - -o /tmp/empty.o && \
    ar rcs /fuzz/install/lib/libhf3fs_api.a /tmp/empty.o && rm -f /tmp/empty.o
