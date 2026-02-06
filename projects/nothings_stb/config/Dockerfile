ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No external dependencies required; header-only libraries.
# Use the required compilers and set install prefix
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

# Install: copy headers into /fuzz/install/include
RUN set -eux; \
    mkdir -p ${PREFIX}/include; \
    cp -v /fuzz/src/stb_*.h ${PREFIX}/include/; \
    :
