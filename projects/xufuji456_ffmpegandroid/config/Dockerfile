ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends build-essential ca-certificates && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz

# Patch problematic headers to include required standard headers
RUN sed -i '/#define NEXT_DICTIONARY_H/a #include <cstdint>\n#include <string>\n#include <cstddef>' /fuzz/src/engine/common/include/NextDictionary.h && \
    sed -i '1i #include <cstring>' /fuzz/src/engine/common/src/NextDictionary.cpp

# Install headers
RUN mkdir -p /fuzz/install/include/nextcommon /fuzz/install/lib /tmp/build && \
    cp -r /fuzz/src/engine/common/include/*.h /fuzz/install/include/nextcommon/

# Build static library with fuzzing compilers
RUN stitch_libafl_cxx -fPIC -O2 -I/fuzz/src/engine/common/include -c /fuzz/src/engine/common/src/NextDictionary.cpp -o /tmp/build/NextDictionary.o && \
    stitch_libafl_cxx -fPIC -O2 -I/fuzz/src/engine/common/include -c /fuzz/src/engine/common/src/NextLog.cpp -o /tmp/build/NextLog.o && \
    ar rcs /fuzz/install/lib/libnextcommon.a /tmp/build/NextDictionary.o /tmp/build/NextLog.o && \
    ranlib /fuzz/install/lib/libnextcommon.a
