ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library from the reusable common components of gImageReader
# and install headers for linking.

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p ${INSTALL_PREFIX}/lib ${INSTALL_PREFIX}/include /tmp/build && \
    cd /fuzz/src/common && \
    $CXX -O2 -fPIC -c CCITTFax4Encoder.cc -o /tmp/build/CCITTFax4Encoder.o && \
    $CXX -O2 -fPIC -c PaperSize.cc -o /tmp/build/PaperSize.o && \
    ar rcs /tmp/build/libgimagereader_common.a /tmp/build/CCITTFax4Encoder.o /tmp/build/PaperSize.o && \
    cp /tmp/build/libgimagereader_common.a ${INSTALL_PREFIX}/lib/ && \
    cp CCITTFax4Encoder.hh PaperSize.hh ${INSTALL_PREFIX}/include/
