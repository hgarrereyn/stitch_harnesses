ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

RUN ./configure --prefix=/fuzz/install \
 && make -j"$(nproc)" \
 && mkdir -p /fuzz/install/lib /fuzz/install/include \
 && find . -name '*.o' -not -path './t/*' -not -name 'fio.o' -print0 | xargs -0 ar rcs libfiofull.a \
 && cp libfiofull.a /fuzz/install/lib/libfio.a \
 && mkdir -p /fuzz/install/include \
 && tar cf - $(find . -type f -name '*.h') | (cd /fuzz/install/include && tar xvf -) \
 && cp fio.h /fuzz/install/include/fio.h
