ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools needed for manual static library build
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      build-essential ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Build a minimal static library for the guarded allocator component.
# This avoids configuring the entire Blender build while still exposing a stable public API.
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install \
    SRC=/fuzz/src

RUN set -eux; \
    mkdir -p "$INSTALL_PREFIX/lib"; \
    cd "$SRC"; \
    # Compile guardedalloc sources
    "$CXX" -O2 -fPIC -I"$SRC" -I"$SRC/intern/guardedalloc" -I"$SRC/intern/atomic" -I"$SRC/source/blender/blenlib" \
      -c "$SRC/intern/guardedalloc/intern/leak_detector.cc" -o leak_detector.o; \
    "$CXX" -O2 -fPIC -I"$SRC" -I"$SRC/intern/guardedalloc" -I"$SRC/intern/atomic" -I"$SRC/source/blender/blenlib" \
      -c "$SRC/intern/guardedalloc/intern/mallocn.cc" -o mallocn.o; \
    "$CXX" -O2 -fPIC -I"$SRC" -I"$SRC/intern/guardedalloc" -I"$SRC/intern/atomic" -I"$SRC/source/blender/blenlib" \
      -c "$SRC/intern/guardedalloc/intern/mallocn_guarded_impl.cc" -o mallocn_guarded_impl.o; \
    "$CXX" -O2 -fPIC -I"$SRC" -I"$SRC/intern/guardedalloc" -I"$SRC/intern/atomic" -I"$SRC/source/blender/blenlib" \
      -c "$SRC/intern/guardedalloc/intern/mallocn_lockfree_impl.cc" -o mallocn_lockfree_impl.o; \
    "$CXX" -O2 -fPIC -I"$SRC" -I"$SRC/intern/guardedalloc" -I"$SRC/intern/atomic" -I"$SRC/source/blender/blenlib" \
      -c "$SRC/intern/guardedalloc/intern/memory_usage.cc" -o memory_usage.o; \
    ar rcs "$INSTALL_PREFIX/lib/libguardedalloc.a" \
      leak_detector.o mallocn.o mallocn_guarded_impl.o mallocn_lockfree_impl.o memory_usage.o; \
    rm -f leak_detector.o mallocn.o mallocn_guarded_impl.o mallocn_lockfree_impl.o memory_usage.o

# Install the public header (kept in source tree, so consumers include via -I/fuzz/src)
# We still create include dir to satisfy consumers expecting an include prefix.
RUN mkdir -p /fuzz/install/include
