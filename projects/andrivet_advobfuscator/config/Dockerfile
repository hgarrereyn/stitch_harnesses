ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and libc++ for full C++20 constexpr support
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config build-essential binutils ca-certificates \
    libc++-17-dev libc++abi-17-dev && \
    rm -rf /var/lib/apt/lists/*

# Use LibAFL compiler wrappers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Build and install the header-only library, then build a small C shim library compiled with C++20
RUN cmake -S /fuzz/src -B /fuzz/build \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_TESTING=OFF -DBUILD_EXAMPLES=OFF \
      -DCMAKE_BUILD_TYPE=Release \
  && cmake --build /fuzz/build --target install \
  # Build a tiny static wrapper library exposing a C ABI that internally uses C++20 ADVobfuscator
  && mkdir -p /fuzz/build/shim /fuzz/install/lib \
  && printf "#include <advobfuscator/string.h>\n#include <string>\n#include <cstdlib>\n#include <cstring>\nextern \"C\" const char* advobf_demo() {\n  using namespace andrivet::advobfuscator;\n  constexpr auto s = \"Hello, ADVobfuscator!\"_obf;\n  std::string d = s.decode();\n  char* out = (char*)std::malloc(d.size()+1);\n  if(!out) return nullptr;\n  std::memcpy(out, d.c_str(), d.size()+1);\n  return out;\n}\n" > /fuzz/build/shim/advobf_shim.cpp \
  && printf "#pragma once\n#ifdef __cplusplus\nextern \"C\" {\n#endif\nconst char* advobf_demo(void);\n#ifdef __cplusplus\n}\n#endif\n" > /fuzz/install/include/advobf_shim.h \
  && gf_libafl_cxx -std=gnu++20 -stdlib=libc++ -I/fuzz/install/include -O2 -c /fuzz/build/shim/advobf_shim.cpp -o /fuzz/build/shim/advobf_shim.o \
  && ar rcs /fuzz/install/lib/libadvobfshim.a /fuzz/build/shim/advobf_shim.o
