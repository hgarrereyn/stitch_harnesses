ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/lib

WORKDIR /fuzz/src/dos2unix
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx AR=ar RANLIB=ranlib CFLAGS="-O2 -fPIC -DVER_REVISION=\"7.5.2\" -DVER_DATE=\"2024-01-22\"" LDFLAGS=""
RUN $CC $CFLAGS -c common.c -o /fuzz/build/common.o && \
    $CC $CFLAGS -Dmain=d2u_cli_main -c dos2unix.c -o /fuzz/build/dos2unix.o && \
    $CC $CFLAGS -c querycp.c -o /fuzz/build/querycp.o && \
    $AR rcs /fuzz/install/lib/libdos2unix.a /fuzz/build/common.o /fuzz/build/dos2unix.o /fuzz/build/querycp.o && \
    $RANLIB /fuzz/install/lib/libdos2unix.a && \
    cp dos2unix.h /fuzz/install/include/ && \
    cp common.h /fuzz/install/include/

WORKDIR /
