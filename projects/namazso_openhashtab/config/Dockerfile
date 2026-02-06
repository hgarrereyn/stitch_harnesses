ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src/OpenHashTab/OpenHashTab

RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include/OpenHashTab \
 && $CXX -std=c++20 -O2 -fPIC \
    -include cstdint -include cstddef -include string -include vector \
    -c base64.cpp -o /fuzz/build/base64.o \
 && ar rcs /fuzz/install/lib/libopenhashtab.a /fuzz/build/base64.o \
 && cp base64.h /fuzz/install/include/OpenHashTab/base64.h \
 && printf '#pragma once\n#include <cstdint>\n#include <cstddef>\n#include <string>\n#include <vector>\n#include "base64.h"\n' > /fuzz/install/include/OpenHashTab/openhashtab.h
