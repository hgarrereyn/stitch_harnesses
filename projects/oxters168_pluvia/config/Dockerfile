ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends build-essential && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

RUN mkdir -p /fuzz/install/lib /fuzz/install/include

WORKDIR /fuzz/src/app/src/main/cpp/proot/talloc

# Build static talloc library and install headers
RUN ${CC} -O2 -fPIC -include stdint.h -c talloc.c -o talloc.o \
    && ar rcs libtalloc.a talloc.o \
    && cp libtalloc.a /fuzz/install/lib/ \
    && cp talloc.h /fuzz/install/include/
