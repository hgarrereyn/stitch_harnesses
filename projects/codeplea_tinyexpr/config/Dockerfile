ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install tinyexpr as a static library
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

WORKDIR /fuzz/src

# No external dependencies are required. Use the provided compiler wrappers
# to build a static library and install headers and archive into /fuzz/install
RUN set -eux; \
    mkdir -p "$PREFIX/include" "$PREFIX/lib"; \
    "$CC" -O2 -fPIC -c tinyexpr.c -o tinyexpr.o; \
    ar rcs libtinyexpr.a tinyexpr.o; \
    install -m 0644 tinyexpr.h "$PREFIX/include/"; \
    install -m 0644 libtinyexpr.a "$PREFIX/lib/"; \
    rm -f tinyexpr.o libtinyexpr.a
