ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib; \
    cp -r /fuzz/src/include/libopencm3 /fuzz/install/include/; \
    cp -r /fuzz/src/include/libopencmsis /fuzz/install/include/; \
    printf 'void __locm3_empty(void){}' > /tmp/empty.c; \
    ${CC:-gf_libafl_cc} -c /tmp/empty.c -o /tmp/empty.o; \
    ar rcs /fuzz/install/lib/libopencm3.a /tmp/empty.o; \
    rm -f /tmp/empty.c /tmp/empty.o

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

