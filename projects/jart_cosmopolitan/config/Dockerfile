ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed to build a static library
RUN apt-get update && apt-get install -y --no-install-recommends binutils ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install

RUN mkdir -p /fuzz/build/libc/runtime /fuzz/install/include /fuzz/install/lib

# Provide a minimal shim for libc/runtime/runtime.h to satisfy puff.c without pulling full libc
RUN printf '%s\n' \
  '#ifndef COSMOPOLITAN_LIBC_RUNTIME_RUNTIME_H_' \
  '#define COSMOPOLITAN_LIBC_RUNTIME_RUNTIME_H_' \
  '#include <stddef.h>' \
  '#include <setjmp.h>' \
  '#define COSMOPOLITAN_C_START_' \
  '#define COSMOPOLITAN_C_END_' \
  '#define libcesque' \
  '#define pureconst' \
  '#define wontreturn' \
  '#define paramsnonnull(...)' \
  '#define __wur' \
  '#define nosideeffect' \
  '#define returnstwice' \
  '#define __write_only(...)' \
  '#define __fd_arg(...)' \
  '#define dontthrow' \
  '#define dontinstrument' \
  '#define __notice(name, text)' \
  '#endif' > /fuzz/build/libc/runtime/runtime.h

WORKDIR /fuzz/build
RUN $CC -O2 -I/fuzz/build -I/fuzz/src -I/fuzz/src/third_party/puff -DCOSMOPOLITAN_C_START_="" -DCOSMOPOLITAN_C_END_="" -c /fuzz/src/third_party/puff/puff.c -o puff.o \
 && ar rcs libpuff.a puff.o \
 && cp /fuzz/src/third_party/puff/puff.h /fuzz/install/include/ \
 && cp libpuff.a /fuzz/install/lib/
