ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      libncurses-dev \
      make \
      ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Environment for compilers
ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

# Build static library manually (avoid data embedding requirements)
WORKDIR /fuzz

RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include && \
    cd /fuzz/build && \
    INCS="-I/fuzz/src/include -I/fuzz/src/data" && \
    CFLAGS="-O2 -fPIC $INCS" && \
    $CC $CFLAGS -c /fuzz/src/src/astro.c -o astro.o && \
    $CC $CFLAGS -c /fuzz/src/src/bit.c -o bit.o && \
    $CC $CFLAGS -c /fuzz/src/src/coord.c -o coord.o && \
    $CC $CFLAGS -c /fuzz/src/src/core.c -o core.o && \
    $CC $CFLAGS -c /fuzz/src/src/core_position.c -o core_position.o && \
    $CC $CFLAGS -c /fuzz/src/src/core_render.c -o core_render.o && \
    $CC $CFLAGS -c /fuzz/src/src/drawing.c -o drawing.o && \
    $CC $CFLAGS -c /fuzz/src/src/parse_BSC5.c -o parse_BSC5.o && \
    $CC $CFLAGS -c /fuzz/src/src/stopwatch.c -o stopwatch.o && \
    $CC $CFLAGS -c /fuzz/src/src/term.c -o term.o && \
    # Provide portable strptime implementation as the project does
    $CC $CFLAGS -c /fuzz/src/src/strptime.c -o strptime.o && \
    ar rcs /fuzz/install/lib/libastroterm.a *.o && \
    cp -r /fuzz/src/include/* /fuzz/install/include/

# Done. The library and headers are in /fuzz/install
