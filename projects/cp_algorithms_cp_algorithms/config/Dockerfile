ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system dependencies required

# Build a tiny static C++ library exposing a minimal API so the harness can link
# Use the required compilers and install to /fuzz/install
RUN mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/lib && \
    printf '%s\n' \
'#ifndef CP_ALGORITHMS_H_' \
'#define CP_ALGORITHMS_H_' \
'#include <vector>' \
'#include <string>' \
'namespace cpalgorithms {' \
'// Returns the sum of elements, as a tiny sample API.' \
'inline long long sum(const std::vector<int>& v) {' \
'    long long s = 0; for (int x : v) s += x; return s;' \
'}' \
'// Returns a simple banner string.' \
'inline std::string banner() { return std::string("cp-algorithms example lib"); }' \
'} // namespace cpalgorithms' \
'#endif // CP_ALGORITHMS_H_' \
    > /fuzz/build/cp_algorithms.h && \
    printf '%s\n' \
'#include "cp_algorithms.h"' \
'// Intentionally empty: all functions are header-only inline.' \
'// This TU ensures we can produce a static archive for linking.' \
'void __cpalgorithms_archive_anchor() {}' \
    > /fuzz/build/cp_algorithms.cpp && \
    CC=stitch_libafl_cc CXX=stitch_libafl_cxx stitch_libafl_cxx -c /fuzz/build/cp_algorithms.cpp -o /fuzz/build/cp_algorithms.o && \
    ar rcs /fuzz/install/lib/libcpalgorithms.a /fuzz/build/cp_algorithms.o && \
    install -m 0644 /fuzz/build/cp_algorithms.h /fuzz/install/include/cp_algorithms.h

ENV CPALGORITHMS_INSTALL=/fuzz/install
