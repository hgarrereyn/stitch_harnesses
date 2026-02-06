ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# bzip2 builds with a simple Makefile. We build the static lib and install headers/libs.
# Use stitch_libafl_cc/stitch_libafl_cxx as compilers and install to /fuzz/install.

WORKDIR /fuzz/src

# Build only required targets to avoid running self-tests, then install
RUN make -j"$(nproc)" \
      CC=stitch_libafl_cc \
      CFLAGS="-O2 -g -D_FILE_OFFSET_BITS=64" \
      libbz2.a bzip2 bzip2recover && \
    make \
      CC=stitch_libafl_cc \
      CFLAGS="-O2 -g -D_FILE_OFFSET_BITS=64" \
      install PREFIX=/fuzz/install && \
    true
