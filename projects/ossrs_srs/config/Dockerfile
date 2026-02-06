ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential ca-certificates pkg-config cmake tcl \
  && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Generate configuration headers with minimal features to avoid heavy deps.
WORKDIR /fuzz/src/trunk
RUN ./configure --jobs=$(nproc) \
    --rtc=off --srt=off --rtsp=off --utest=off \
    --ffmpeg-fit=off --ffmpeg-opus=off --https=off \
    --sys-ssl=on --cc=gf_libafl_cc --cxx=gf_libafl_cxx

# Build a lightweight static library from core/ only and install headers + lib.
RUN install -d /fuzz/install/include /fuzz/install/lib \
  && cp -v src/core/*.hpp /fuzz/install/include/ \
  && cp -v objs/srs_auto_headers.hpp /fuzz/install/include/

# Compile core sources into a static library.
RUN bash -lc 'set -euo pipefail; \
  objs_dir=/tmp/srs_core_objs; mkdir -p ${objs_dir}; \
  for f in src/core/*.cpp; do \
    gf_libafl_cxx -I/fuzz/install/include -I./src -I./src/core -c "$f" -o ${objs_dir}/$(basename "$f" .cpp).o; \
  done; \
  ar rcs /fuzz/install/lib/libsrscore.a ${objs_dir}/*.o; \
  ranlib /fuzz/install/lib/libsrscore.a'
