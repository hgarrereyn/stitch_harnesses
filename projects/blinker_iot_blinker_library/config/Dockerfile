ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools (cmake, ninja)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Create Arduino compatibility stubs to allow building a minimal subset
RUN mkdir -p /fuzz/src/stubs && \
    printf "#pragma once\n#include <cstdint>\n#include <string>\n#include <iostream>\n#define F(x) x\n#define PROGMEM\ntypedef std::string String;\nclass Stream { public: template<typename T> void print(const T& v){ std::cout<<v; } template<typename T> void println(const T& v){ std::cout<<v<<std::endl; } void println(){ std::cout<<std::endl; } };\ninline uint32_t millis(){ return 0; }\n" > /fuzz/src/stubs/Arduino.h && \
    printf "#pragma once\n#include \"Arduino.h\"\n" > /fuzz/src/stubs/WProgram.h && \
    printf "#pragma once\n#define PROGMEM\n" > /fuzz/src/stubs/pgmspace.h

# Create a simple CMakeLists.txt to build a static library
RUN printf "cmake_minimum_required(VERSION 3.16)\nset(CMAKE_C_COMPILER gf_libafl_cc)\nset(CMAKE_CXX_COMPILER gf_libafl_cxx)\nproject(blinker LANGUAGES CXX C)\nset(CMAKE_INSTALL_PREFIX /fuzz/install)\nadd_library(blinker STATIC src/Blinker/BlinkerDebug.cpp)\ntarget_include_directories(blinker PRIVATE src stubs)\ntarget_include_directories(blinker PUBLIC \$<INSTALL_INTERFACE:include>)\ntarget_compile_definitions(blinker PUBLIC ARDUINO=100)\ninstall(TARGETS blinker ARCHIVE DESTINATION lib)\ninstall(FILES src/Blinker/BlinkerDebug.h DESTINATION include/Blinker)\ninstall(FILES stubs/Arduino.h stubs/WProgram.h stubs/pgmspace.h DESTINATION include)\n" > /fuzz/src/CMakeLists.txt && \
    mkdir -p /fuzz/build && \
    cd /fuzz/build && \
    CC=gf_libafl_cc CXX=gf_libafl_cxx cmake -G Ninja /fuzz/src && \
    ninja && \
    ninja install
