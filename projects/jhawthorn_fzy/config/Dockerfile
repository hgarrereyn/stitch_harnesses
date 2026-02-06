ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/src

RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp src/config.def.h config.h && \
    ${CC} -O2 -fPIC -Ideps -Isrc -c src/match.c -o /tmp/match.o && \
    ar rcs /fuzz/install/lib/libfzy.a /tmp/match.o && \
    cp src/match.h src/choices.h src/options.h /fuzz/install/include/
