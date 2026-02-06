ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install

RUN mkdir -p ${PREFIX}/include/Algorithm ${PREFIX}/lib && \
    cp -v /fuzz/src/Algorithm/*.h ${PREFIX}/include/Algorithm/ && \
    printf "#pragma once\n#include <vector>\n#include <algorithm>\n#include <utility>\nusing namespace std;\n#include \"Algorithm/BubbleSort.h\"\n#include \"Algorithm/SelectionSort.h\"\n" > ${PREFIX}/include/interview_algorithms.hpp && \
    printf "void __interview_dummy(void){}" > /tmp/dummy.c && \
    ${CC} -c /tmp/dummy.c -o /tmp/dummy.o && \
    ar rcs ${PREFIX}/lib/libinterview.a /tmp/dummy.o && \
    rm -f /tmp/dummy.c /tmp/dummy.o
