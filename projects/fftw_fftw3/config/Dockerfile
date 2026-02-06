ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Use provided clang wrappers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure and build static library using CMake
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTS=OFF \
    -DENABLE_OPENMP=OFF \
    -DENABLE_THREADS=OFF \
    -DENABLE_SSE=OFF \
    -DENABLE_SSE2=OFF \
    -DENABLE_AVX=OFF \
    -DENABLE_AVX2=OFF

RUN cmake --build build --target install --config Release

# Build stub library to satisfy missing generated symbol references when linking
RUN printf '%s\n' \
  'void *fftw_solvtab_dft_standard = 0;' \
  'void *fftw_solvtab_rdft_r2cf = 0;' \
  'void *fftw_solvtab_rdft_r2cb = 0;' \
  'void *fftw_solvtab_rdft_r2r = 0;' \
  > /tmp/fftw_stubs.c
RUN gf_libafl_cc -c /tmp/fftw_stubs.c -o /tmp/fftw_stubs.o && \
    ar rcs /fuzz/install/lib/libfftw3_stub.a /tmp/fftw_stubs.o && \
    rm -f /tmp/fftw_stubs.c /tmp/fftw_stubs.o
