ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools for creating a static library (ar, etc.)
RUN apt-get update && apt-get install -y --no-install-recommends build-essential && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Build a static libxs.a from the XS engine sources and install public headers
RUN set -eux; \
    SRCDIR=/fuzz/src/xs; \
    INCDIR="$SRCDIR/includes"; \
    PLATDIR="$SRCDIR/platforms"; \
    SRCDSRC="$SRCDIR/sources"; \
    mkdir -p /tmp/build/objs; \
    for f in "$SRCDSRC"/*.c; do \
      gf_libafl_cc -fPIC -O2 -g -I"$INCDIR" -I"$PLATDIR" -I"$SRCDSRC" -c "$f" -o "/tmp/build/objs/$(basename "${f%.c}.o")"; \
    done; \
    ar rcs /tmp/build/libxs.a /tmp/build/objs/*.o; \
    mkdir -p /fuzz/install/lib /fuzz/install/include; \
    cp /tmp/build/libxs.a /fuzz/install/lib/; \
    cp "$INCDIR"/*.h /fuzz/install/include/

ENV CPATH=/fuzz/install/include LIBRARY_PATH=/fuzz/install/lib
