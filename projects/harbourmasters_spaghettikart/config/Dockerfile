ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -r /fuzz/src/include/ /fuzz/install/

RUN echo 'void sk_dummy(void){}' > /tmp/dummy.c \
 && ${CC} -c /tmp/dummy.c -o /tmp/dummy.o \
 && ar rcs /fuzz/install/lib/libspaghettikart.a /tmp/dummy.o \
 && rm -f /tmp/dummy.c /tmp/dummy.o
