ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies: meson, pkg-config, and python3 runtime for meson
RUN apt-get update && apt-get install -y --no-install-recommends \
    meson pkg-config python3 \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libfuse with meson/ninja
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx
WORKDIR /fuzz/src

# Build only the library (no utils/examples/tests) and disable io_uring + libc symbol versions
RUN meson setup build \
      --prefix=/fuzz/install \
      -Ddefault_library=shared \
      -Dutils=false -Dexamples=false -Dtests=false -Duseroot=false \
      -Denable-io-uring=false -Ddisable-libc-symbol-version=true \
  && ninja -C build \
  && ninja -C build install
