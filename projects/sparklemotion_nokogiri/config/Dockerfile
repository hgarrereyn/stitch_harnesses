ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install the bundled gumbo-parser (C library) as a static library
# using the fuzzer compiler wrappers.
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib; \
    cd /fuzz/src/gumbo-parser/src; \
    for f in *.c; do \
      echo "Compiling $f"; \
      "$CC" -std=c99 -O2 -fPIC -Wall -I. -c "$f" -o "$(basename "$f" .c).o"; \
    done; \
    ar rcs /fuzz/install/lib/libgumbo.a *.o; \
    cp -v nokogiri_gumbo.h /fuzz/install/include/
