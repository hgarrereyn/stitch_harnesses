ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Prepare install prefix and install a lightweight public header
RUN mkdir -p /fuzz/install/include/obs-backgroundremoval \
 && install -D /fuzz/src/src/consts.h /fuzz/install/include/obs-backgroundremoval/consts.h

# Set compilers as required
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
ENV CFLAGS="" CXXFLAGS="" LDFLAGS=""
