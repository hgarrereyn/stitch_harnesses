ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system packages required

# Build and install a minimal static library from the PC iso2opl tool
# exposing a simple ISO9660 reader API
RUN mkdir -p /fuzz/build && \
    cd /fuzz/build && \
    stitch_libafl_cc -O2 -D_LARGEFILE64_SOURCE -c /fuzz/src/pc/iso2opl/src/isofs.c -I/fuzz/src/pc/iso2opl/src -o isofs.o && \
    ar rcs libiso2opl.a isofs.o && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp libiso2opl.a /fuzz/install/lib/ && \
    cp /fuzz/src/pc/iso2opl/src/iso2opl.h /fuzz/install/include/
