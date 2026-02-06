ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system dependencies required. Project depends on Intel Pin for full build,
# which is not needed for exposing header-only utility used for testing.

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

RUN mkdir -p ${INSTALL_PREFIX}/include ${INSTALL_PREFIX}/lib && \
    cp /fuzz/src/Util.h ${INSTALL_PREFIX}/include/Util.h && \
    # Create a dummy static library for linkage if needed
    printf "\n" > /tmp/dummy.c && \
    ${CC} -c /tmp/dummy.c -o /tmp/dummy.o && \
    ar rcs ${INSTALL_PREFIX}/lib/libtinytracer.a /tmp/dummy.o
