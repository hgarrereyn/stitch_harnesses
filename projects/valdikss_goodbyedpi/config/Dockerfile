ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a tiny static library from the portable utility sources
RUN mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/lib

WORKDIR /fuzz/src
RUN stitch_libafl_cc -O2 -fPIC -DHAVE_GETLINE=1 -DHAVE_GETDELIM=1 -c src/utils/repl_str.c -o /fuzz/build/repl_str.o && \
    stitch_libafl_cc -O2 -fPIC -DHAVE_GETLINE=1 -DHAVE_GETDELIM=1 -c src/utils/getline.c -o /fuzz/build/getline.o && \
    ar rcs /fuzz/install/lib/libgoodbyedpi_utils.a /fuzz/build/repl_str.o /fuzz/build/getline.o && \
    cp src/utils/repl_str.h /fuzz/install/include/ && \
    cp src/utils/getline.h /fuzz/install/include/ && \
    cp src/utils/uthash.h /fuzz/install/include/

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
