ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

# Build a minimal static library from Rubinius utilities (timer, file) and a tiny logger shim
RUN mkdir -p /tmp/rbxutil && \
    printf "#include <cstdarg>\nnamespace rubinius { namespace logger {\nvoid open(int, int, const char*, ...){}\nvoid reset(){}\nvoid lock(){}\nbool try_lock(){return false;}\nvoid unlock(){}\nvoid close(){}\nvoid write(const char*, ... ){}\nvoid fatal(const char*, ... ){}\nvoid error(const char*, ... ){}\nvoid warn(const char*, ... ){}\nvoid info(const char*, ... ){}\nvoid debug(const char*, ... ){}\nvoid write(const char*, va_list){}\nvoid fatal(const char*, va_list){}\nvoid error(const char*, va_list){}\nvoid warn(const char*, va_list){}\nvoid info(const char*, va_list){}\nvoid debug(const char*, va_list){}\nvoid set_loglevel(int){}\n} }\n" > /tmp/rbxutil/min_logger.cpp && \
    printf "cmake_minimum_required(VERSION 3.16)\n" > /tmp/rbxutil/CMakeLists.txt && \
    printf "project(rbxutil LANGUAGES C CXX)\n" >> /tmp/rbxutil/CMakeLists.txt && \
    printf "add_library(rbxutil STATIC\n  /tmp/rbxutil/min_logger.cpp\n  /fuzz/src/machine/util/timer.cpp\n  /fuzz/src/machine/util/file.cpp\n)\n" >> /tmp/rbxutil/CMakeLists.txt && \
    printf "target_include_directories(rbxutil PUBLIC /fuzz/src/machine /fuzz/src)\n" >> /tmp/rbxutil/CMakeLists.txt && \
    printf "target_compile_definitions(rbxutil PUBLIC HAVE_TIMERFD=1)\n" >> /tmp/rbxutil/CMakeLists.txt && \
    printf "set_target_properties(rbxutil PROPERTIES OUTPUT_NAME rbxutil)\n" >> /tmp/rbxutil/CMakeLists.txt && \
    printf "install(TARGETS rbxutil ARCHIVE DESTINATION lib)\n" >> /tmp/rbxutil/CMakeLists.txt && \
    printf "install(FILES\n  /fuzz/src/machine/defines.hpp\n  /fuzz/src/machine/spinlock.hpp\n  /fuzz/src/machine/logger.hpp\n  DESTINATION include/rubinius)\n" >> /tmp/rbxutil/CMakeLists.txt && \
    printf "install(FILES\n  /fuzz/src/machine/util/optimize.hpp\n  /fuzz/src/machine/util/file.hpp\n  /fuzz/src/machine/util/timer.hpp\n  DESTINATION include/rubinius/util)\n" >> /tmp/rbxutil/CMakeLists.txt && \
    cmake -S /tmp/rbxutil -B /tmp/rbxutil/build -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install && \
    cmake --build /tmp/rbxutil/build --config Release && \
    cmake --install /tmp/rbxutil/build --config Release
