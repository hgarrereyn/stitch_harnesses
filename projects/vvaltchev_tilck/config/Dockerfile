ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

# Install minimal headers and provide generated config stand-ins
RUN mkdir -p /fuzz/install/include/tilck /fuzz/install/include/tilck_gen_headers && \
    cp -r /fuzz/src/include/tilck/* /fuzz/install/include/tilck/ && \
    /bin/sh -c 'printf "#pragma once\n/* minimal kernel config for header-only use */\n" > /fuzz/install/include/tilck_gen_headers/config_kernel.h' && \
    /bin/sh -c 'printf "#pragma once\n/* minimal global config for header-only use */\n#define ARCH_BITS 64\n#define DEBUG_CHECKS 0\n" > /fuzz/install/include/tilck_gen_headers/config_global.h'
