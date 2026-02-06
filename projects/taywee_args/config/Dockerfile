ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install header using provided Makefile (header-only library)
RUN make -C /fuzz/src install DESTDIR=/fuzz/install CC=stitch_libafl_cc CXX=stitch_libafl_cxx
