ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install FFmpeg as static libraries into /fuzz/install
WORKDIR /fuzz/src

# Configure for static libs only, no programs or docs; disable x86 asm to avoid nasm/yasm dependency
RUN ./configure \
    --prefix=/fuzz/install \
    --cc=stitch_libafl_cc \
    --cxx=stitch_libafl_cxx \
    --disable-shared \
    --enable-static \
    --disable-programs \
    --disable-doc \
    --disable-debug \
    --disable-x86asm \
  && make -j"$(nproc)" \
  && make install
