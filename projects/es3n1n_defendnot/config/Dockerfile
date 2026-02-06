ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Prepare install prefix and export a tiny static lib plus a minimal public header
RUN set -eux; \
    install -d /fuzz/install/include /fuzz/install/lib; \
    printf '%s\n' '#pragma once' '#include <string>' 'namespace defendnot_api {' 'inline const char* version() noexcept { return "defendnot-compat-1.0"; }' 'inline std::string greet(const std::string& name) { return std::string("hello, ") + name; }' '}' > /fuzz/install/include/defendnot_api.hpp; \
    echo 'void __defendnot_dummy(){}' > /tmp/dummy.c; \
    gf_libafl_cc -c -O2 -fPIC /tmp/dummy.c -o /tmp/dummy.o; \
    ar rcs /fuzz/install/lib/libdefendnot.a /tmp/dummy.o

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
