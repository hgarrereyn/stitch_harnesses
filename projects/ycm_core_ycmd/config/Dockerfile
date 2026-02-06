ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3-dev \
    libabsl-dev \
    ninja-build \
    cmake \
    make \
 && rm -rf /var/lib/apt/lists/*

# Configure and build ycmd C++ core (ycm_core) with system Abseil (builds the Python module)
RUN cmake -S /fuzz/src/cpp -B /tmp/build \
      -G Ninja \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DCMAKE_BUILD_TYPE=Release \
      -DUSE_SYSTEM_ABSEIL=ON \
      -DUSE_CLANG_COMPLETER=OFF \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
 && cmake --build /tmp/build -j || true

# Install headers and build a linkable shared library from core sources (no Python binding)
RUN mkdir -p /fuzz/install/include/ycm /fuzz/install/lib \
 && cp /fuzz/src/cpp/ycm/*.h /fuzz/install/include/ycm/ \
 && gf_libafl_cxx -std=c++17 -O2 -fPIC -DYCM_EXPORT= -I/fuzz/src/cpp/ycm -c \
      /fuzz/src/cpp/ycm/Utils.cpp \
      /fuzz/src/cpp/ycm/CodePoint.cpp \
      /fuzz/src/cpp/ycm/Character.cpp \
      /fuzz/src/cpp/ycm/Repository.cpp \
      /fuzz/src/cpp/ycm/Candidate.cpp \
      /fuzz/src/cpp/ycm/Result.cpp \
      /fuzz/src/cpp/ycm/Word.cpp \
 && gf_libafl_cxx -shared -o /fuzz/install/lib/libycm_core.so \
      Utils.o CodePoint.o Character.o Repository.o Candidate.o Result.o Word.o \
 && rm -f Utils.o CodePoint.o Character.o Repository.o Candidate.o Result.o Word.o \
 && cp /fuzz/src/ycm_core*.so /fuzz/install/lib/ || true
