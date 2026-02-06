ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and libc++ for full C++20/23 headers (e.g., <format>)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
    libc++-17-dev libc++abi-17-dev \
    && rm -rf /var/lib/apt/lists/*

# Workaround: define std::unreachable if missing in libstdc++ (not needed with libc++, but harmless)
RUN printf "#pragma once\n#include <utility>\n#include <cstdlib>\nnamespace std {\n#if __cpp_lib_unreachable >= 202202L\n/* available */\n#else\n[[noreturn]] inline void unreachable() {\n# if defined(__has_builtin)\n#  if __has_builtin(__builtin_unreachable)\n    __builtin_unreachable();\n#  else\n    __builtin_trap();\n#  endif\n# else\n    std::abort();\n# endif\n}\n#endif\n}\n" > /fuzz/src/compat_unreachable.hpp

# Configure, build, and install log4cplus as a static library
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DLOG4CPLUS_BUILD_TESTING=OFF \
    -DLOG4CPLUS_BUILD_LOGGINGSERVER=OFF \
    -DLOG4CPLUS_QT4=OFF -DLOG4CPLUS_QT5=OFF -DLOG4CPLUS_QT6=OFF \
    -DCMAKE_CXX_FLAGS="-stdlib=libc++ -include /fuzz/src/compat_unreachable.hpp"
RUN cmake --build build --target install
