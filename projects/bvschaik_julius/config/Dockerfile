ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra packages needed for building a small static library
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Build and install a minimal static library exposing Julius core API headers
RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include && \
    "$CC" -c -O2 -Isrc -I/fuzz/src/src /fuzz/src/src/core/time.c -o /fuzz/build/time.o && \
    ar rcs /fuzz/install/lib/libjulius.a /fuzz/build/time.o && \
    cd /fuzz/src/src && \
    find . -type f -name '*.h' -exec install -D '{}' "/fuzz/install/include/{}" ';'
