ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library from a small, self-contained part of the project (Utf8)
# and install public headers into /fuzz/install. This avoids pulling the full Qt stack.

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib; \
    # Build static library from utf8.cc
    ${CXX} -O2 -fPIC -I/fuzz/src -c /fuzz/src/utf8.cc -o /tmp/utf8.o; \
    ar rcs /fuzz/install/lib/libgoldendict_utf8.a /tmp/utf8.o; \
    # Install headers required to use the Utf8 API
    cp /fuzz/src/utf8.hh /fuzz/install/include/; \
    cp /fuzz/src/wstring.hh /fuzz/install/include/; \
    cp /fuzz/src/ex.hh /fuzz/install/include/; \
    cp /fuzz/src/cpp_features.hh /fuzz/install/include/
