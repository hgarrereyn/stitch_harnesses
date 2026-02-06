ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal deps; produce a tiny static lib/archive and a minimal public header
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src
RUN mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/lib && \
    printf "int helio_lib_dummy = 0;\n" > /fuzz/build/helio_dummy.cpp && \
    ${CXX} -c /fuzz/build/helio_dummy.cpp -o /fuzz/build/helio_dummy.o && \
    ar rcs /fuzz/install/lib/libhelio.a /fuzz/build/helio_dummy.o && \
    printf "#pragma once\nnamespace Globals { static constexpr int ticksPerBeat = 16; }\nconstexpr unsigned int fnv1a32val = 0x811c9dc5u;\nconstexpr unsigned long long fnv1a32prime = 0x1000193ull;\ninline constexpr unsigned int constexprHash(const char* const str, const unsigned int value = fnv1a32val) noexcept {\n    return (str[0] == '\\0') ? value : constexprHash(&str[1], (unsigned int)((value ^ (unsigned int)str[0]) * fnv1a32prime));\n}\n" > /fuzz/install/include/helio_minimal.h
