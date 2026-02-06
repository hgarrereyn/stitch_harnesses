ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools to build a tiny static library
RUN apt-get update && apt-get install -y --no-install-recommends binutils ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

# Install headers from the project that are host-buildable
RUN mkdir -p ${PREFIX}/include/arduino-esp32 ${PREFIX}/lib \
 && cp -v /fuzz/src/cores/esp32/binary.h ${PREFIX}/include/arduino-esp32/ \
 && cp -v /fuzz/src/cores/esp32/pgmspace.h ${PREFIX}/include/arduino-esp32/ \
 && cp -v /fuzz/src/cores/esp32/Printable.h ${PREFIX}/include/arduino-esp32/

# Build a minimal static library to link against (subset placeholder)
RUN bash -lc 'echo "int arduino_esp32_subset_placeholder(){return 42;}" > /tmp/placeholder.c \
 && ${CC} -c -O2 /tmp/placeholder.c -o /tmp/placeholder.o \
 && ar rcs ${PREFIX}/lib/libarduino_esp32_subset.a /tmp/placeholder.o \
 && rm -f /tmp/placeholder.c /tmp/placeholder.o'
