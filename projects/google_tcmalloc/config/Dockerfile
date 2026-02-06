ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install deps for Bazel and general build utilities
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    python3 \
    unzip \
    zip \
    rsync \
    binutils \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

# Build the tcmalloc static library object with Bazel (work around restrict on member functions)
RUN bazel build -c opt \
    --cxxopt=-D__restrict__= --conlyopt=-D__restrict__= \
    --cxxopt=-Wno-error --conlyopt=-Wno-error \
    //tcmalloc:tcmalloc

# Install headers (and keep object for reference) into /fuzz/install
RUN set -eux; \
    install -d /fuzz/install/lib /fuzz/install/include/tcmalloc /fuzz/install/include/tcmalloc/internal; \
    bazelbin="$(bazel info bazel-bin -c opt)"; \
    obj=""; \
    if [ -f "$bazelbin/tcmalloc/libtcmalloc.lo" ]; then \
      obj="$bazelbin/tcmalloc/libtcmalloc.lo"; \
    else \
      obj="$(find "$bazelbin/tcmalloc" -maxdepth 1 -type f -name 'libtcmalloc*' | head -n1)"; \
    fi; \
    echo "Found object: $obj"; \
    [ -n "$obj" ] && cp "$obj" /fuzz/install/lib/tcmalloc.o || true; \
    cp -a tcmalloc/*.h /fuzz/install/include/tcmalloc/; \
    cp -a tcmalloc/internal/*.h /fuzz/install/include/tcmalloc/internal/; \
    # Copy Abseil headers used by public API (support multiple external names)
    root="$(bazel info execution_root -c opt)"; \
    for d in "$root"/external/*/absl; do \
      if [ -d "$d" ]; then \
        cp -a "$d" /fuzz/install/include/; \
      fi; \
    done
