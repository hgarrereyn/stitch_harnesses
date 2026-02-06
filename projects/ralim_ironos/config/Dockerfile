ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal tools: we only need an archiver
RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx
ENV PREFIX=/fuzz/install

# Build BriefLZ as a static library and install headers
RUN set -eux; \
    mkdir -p "$PREFIX/include" "$PREFIX/lib"; \
    cd /fuzz/src/source/Core/brieflz; \
    $CC -O2 -fPIC -c brieflz.c -o /tmp/brieflz.o; \
    $CC -O2 -fPIC -c depack.c -o /tmp/depack.o; \
    ar rcs "$PREFIX/lib/libbrieflz.a" /tmp/brieflz.o /tmp/depack.o; \
    cp brieflz.h "$PREFIX/include/"; \
    echo "Installed libbrieflz.a and brieflz.h to $PREFIX";
