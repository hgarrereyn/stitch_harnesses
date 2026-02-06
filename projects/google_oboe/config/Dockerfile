ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal build to create a host-usable static lib that exposes version APIs.
# Oboe targets Android; many sources depend on Android NDK. We only compile
# portable parts (Version.cpp) and install full public headers for consumption.

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install SRC=/fuzz/src

# Build a tiny static library with portable sources only and install headers
RUN mkdir -p /fuzz/build "$PREFIX/lib" "$PREFIX/include" \
 && cd /fuzz/build \
 && "$CXX" -O2 -fPIC -I"$SRC/include" -c "$SRC/src/common/Version.cpp" -o version.o \
 && ar rcs liboboe.a version.o \
 && install -m 0644 liboboe.a "$PREFIX/lib/" \
 && mkdir -p "$PREFIX/include/oboe" \
 && cp -r "$SRC/include/oboe/." "$PREFIX/include/oboe/"
