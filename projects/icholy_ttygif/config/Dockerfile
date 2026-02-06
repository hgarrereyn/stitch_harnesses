ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a static library from the project sources
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Build only the reusable parts (exclude ttygif.c which has main)
RUN set -eux; \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include; \
    ${CC} -O2 -Wall -DOS_LINUX -DVERSION='"1.4.0"' -c io.c -o io.o; \
    ${CC} -O2 -Wall -DOS_LINUX -DVERSION='"1.4.0"' -c string_builder.c -o string_builder.o; \
    ${CC} -O2 -Wall -DOS_LINUX -DVERSION='"1.4.0"' -c utils.c -o utils.o; \
    ar rcs libttygif.a io.o string_builder.o utils.o; \
    cp libttygif.a ${PREFIX}/lib/; \
    cp io.h string_builder.h utils.h ttyrec.h ${PREFIX}/include/
