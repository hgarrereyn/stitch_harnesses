ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN mkdir -p /fuzz/install/include \
 && cp /fuzz/src/gfwx.h /fuzz/install/include/gfwx_original.h \
 && /bin/sh -lc 'printf "%s\n" \
  "#pragma once" \
  "// Wrapper header to provide minimal C++17-compatible polyfills and include the library" \
  "#if __cplusplus < 202002L" \
  "namespace std {" \
  "inline constexpr int bit_width(unsigned int x) { return x ? 8*int(sizeof(unsigned int)) - __builtin_clz(x) : 0; }" \
  "inline constexpr int bit_width(unsigned long x) { return x ? 8*int(sizeof(unsigned long)) - __builtin_clzl(x) : 0; }" \
  "inline constexpr int bit_width(unsigned long long x) { return x ? 8*int(sizeof(unsigned long long)) - __builtin_clzll(x) : 0; }" \
  "}" \
  "#endif" \
  "#include \"gfwx_original.h\"" \
  > /fuzz/install/include/gfwx.h'
