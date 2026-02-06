ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
    pkg-config \
    libabsl-dev \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

RUN mkdir -p /fuzz/build /fuzz/install/include/http_pattern_matcher /fuzz/install/include/include/http_pattern_matcher /fuzz/install/lib && \
    "$CXX" -O2 -fPIC -I/fuzz/src -I/fuzz/src/include -c src/http_template.cc -o /fuzz/build/http_template.o && \
    "$CXX" -O2 -fPIC -I/fuzz/src -I/fuzz/src/include -c src/path_matcher_node.cc -o /fuzz/build/path_matcher_node.o && \
    "$CXX" -O2 -fPIC -I/fuzz/src -I/fuzz/src/include -c src/path_matcher.cc -o /fuzz/build/path_matcher.o && \
    ar rcs /fuzz/install/lib/libhttp_pattern_matcher.a /fuzz/build/http_template.o /fuzz/build/path_matcher_node.o /fuzz/build/path_matcher.o && \
    cp include/http_pattern_matcher/*.h /fuzz/install/include/http_pattern_matcher/ && \
    cp include/http_pattern_matcher/*.h /fuzz/install/include/include/http_pattern_matcher/
