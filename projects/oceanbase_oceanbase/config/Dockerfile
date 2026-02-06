ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal install: expose a tiny public header and a stub static library

# Create install prefix and copy selected public headers from source tree
RUN mkdir -p /fuzz/install/include/lib/hash_func /fuzz/install/lib \
 && install -m 0644 -D /fuzz/src/deps/oblib/src/lib/hash_func/murmur_hash.h /fuzz/install/include/lib/hash_func/murmur_hash.h

# Build a tiny static library to link against (no external deps)
RUN echo 'void ob_dummy(){}' > /tmp/ob_dummy.c \
 && gf_libafl_cc -c /tmp/ob_dummy.c -o /tmp/ob_dummy.o \
 && ar rcs /fuzz/install/lib/liboceanbase.a /tmp/ob_dummy.o \
 && rm -f /tmp/ob_dummy.c /tmp/ob_dummy.o

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
ENV INSTALL_PREFIX=/fuzz/install
