ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library for Blender's guarded allocator without full project configuration.
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      make \
    && rm -rf /var/lib/apt/lists/*

# Compile guardedalloc sources with the provided clang wrappers and archive into a static library.
RUN set -ex; \
    mkdir -p /fuzz/build/guardedalloc && cd /fuzz/build/guardedalloc; \
    INC="-I/fuzz/src/intern/guardedalloc -I/fuzz/src/intern/guardedalloc/intern -I/fuzz/src/intern/atomic -I/fuzz/src/source/blender/blenlib"; \
    SRCDIR=/fuzz/src/intern/guardedalloc/intern; \
    gf_libafl_cxx -O2 -g $INC -c $SRCDIR/leak_detector.cc -o leak_detector.o; \
    gf_libafl_cxx -O2 -g $INC -c $SRCDIR/mallocn.cc -o mallocn.o; \
    gf_libafl_cxx -O2 -g $INC -c $SRCDIR/mallocn_guarded_impl.cc -o mallocn_guarded_impl.o; \
    gf_libafl_cxx -O2 -g $INC -c $SRCDIR/mallocn_lockfree_impl.cc -o mallocn_lockfree_impl.o; \
    gf_libafl_cxx -O2 -g $INC -c $SRCDIR/memory_usage.cc -o memory_usage.o; \
    ar rcs libbf_intern_guardedalloc.a leak_detector.o mallocn.o mallocn_guarded_impl.o mallocn_lockfree_impl.o memory_usage.o; \
    mkdir -p /fuzz/install/lib && cp libbf_intern_guardedalloc.a /fuzz/install/lib/; \
    # Install headers required to use the public API.
    mkdir -p /fuzz/install/include/intern/guardedalloc/intern && \
    mkdir -p /fuzz/install/include/source/blender/blenlib && \
    cp /fuzz/src/intern/guardedalloc/MEM_guardedalloc.h /fuzz/install/include/intern/guardedalloc/ && \
    cp /fuzz/src/intern/guardedalloc/intern/*.hh /fuzz/install/include/intern/guardedalloc/intern/ && \
    cp /fuzz/src/source/blender/blenlib/BLI_compiler_attrs.h /fuzz/install/include/source/blender/blenlib/ && \
    cp /fuzz/src/source/blender/blenlib/BLI_sys_types.h /fuzz/install/include/source/blender/blenlib/
