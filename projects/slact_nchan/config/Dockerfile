ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No special dependencies are needed to expose the public header.
# We still set compilers for consistency, though we are not building anything heavy here.
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Install step: copy public headers into the install prefix
RUN mkdir -p /fuzz/install/include \
 && cp /fuzz/src/src/nchan_version.h /fuzz/install/include/
