ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for building
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    python3-minimal \
    cmake \
    binutils \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    CMAKE_INSTALL_PREFIX=/fuzz/install

# Configure with CMake (no tests, binary optional). We just generate build files.
RUN cmake -S /fuzz/src -B /fuzz/build \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_TESTING=OFF \
    -DNINJA_BUILD_BINARY=OFF \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install && \
    cmake --build /fuzz/build -j$(nproc)

# Manually create a small static library exposing version API and install headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/ninja && \
    "$CXX" -I/fuzz/src/src -c /fuzz/src/src/version.cc -o /tmp/version.o && \
    printf '#include <cstdarg>\n#include <cstdlib>\nvoid Warning(const char* msg, ...) {}\nvoid Warning(const char* msg, va_list ap) {}\nvoid Error(const char* msg, ...) {}\nvoid Error(const char* msg, va_list ap) {}\nvoid Info(const char* msg, ...) {}\nvoid Info(const char* msg, va_list ap) {}\n[[noreturn]] void Fatal(const char* msg, ...) { std::abort(); }\n' > /tmp/ninja_util_stubs.cpp && \
    "$CXX" -c /tmp/ninja_util_stubs.cpp -o /tmp/ninja_util_stubs.o && \
    ar rcs /fuzz/install/lib/libninjaversion.a /tmp/version.o /tmp/ninja_util_stubs.o && \
    cp /fuzz/src/src/version.h /fuzz/install/include/ninja/version.h && \
    rm -f /tmp/version.o /tmp/ninja_util_stubs.o /tmp/ninja_util_stubs.cpp
