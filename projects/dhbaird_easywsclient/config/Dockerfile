ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install easywsclient as a static library
RUN set -eux; \
    export CC=stitch_libafl_cc CXX=stitch_libafl_cxx; \
    mkdir -p /fuzz/install/include /fuzz/install/lib; \
    cd /fuzz/src; \
    $CXX -O2 -fPIC -c easywsclient.cpp -o easywsclient.o; \
    ar rcs libeasywsclient.a easywsclient.o; \
    cp easywsclient.hpp /fuzz/install/include/; \
    cp libeasywsclient.a /fuzz/install/lib/
