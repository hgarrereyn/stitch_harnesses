ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p "$PREFIX/include/houjie" "$PREFIX/lib"; \
    cp -v /fuzz/src/C++-OOPBase1-HouJie/code/complex.h "$PREFIX/include/houjie/complex.h"; \
    cp -v /fuzz/src/C++-OOPBase1-HouJie/code/string.h "$PREFIX/include/houjie/string.h"; \
    # create a tiny static library to satisfy linkers
    echo 'void bilibili_plus_dummy(void){}' > /tmp/dummy.c; \
    $CC -c /tmp/dummy.c -o /tmp/dummy.o; \
    ar rcs "$PREFIX/lib/libhoujie.a" /tmp/dummy.o; \
    rm -f /tmp/dummy.c /tmp/dummy.o
