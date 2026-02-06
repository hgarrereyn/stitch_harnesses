ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build CLD2 static library from the project's bundled sources
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install

# Compile CLD2 and install headers and static lib
RUN set -eux; \
    SRCDIR="/fuzz/src/src/lib/cld2"; \
    mkdir -p /tmp/build/cld2 && cd /tmp/build/cld2; \
    INCFLAGS="-I${SRCDIR}/internal -I${SRCDIR}/public"; \
    CXXFLAGS_EXTRA="-O2 -fPIC -Wno-c++11-narrowing"; \
    for f in ${SRCDIR}/internal/*.cc; do \
      ${CXX} ${CXXFLAGS_EXTRA} ${INCFLAGS} -c "$f" -o "$(basename "$f" .cc).o"; \
    done; \
    ar rcs libcld2.a *.o; \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include/cld2/public ${PREFIX}/include/cld2/internal; \
    cp libcld2.a ${PREFIX}/lib/; \
    cp ${SRCDIR}/public/*.h ${PREFIX}/include/cld2/public/; \
    cp ${SRCDIR}/internal/*.h ${PREFIX}/include/cld2/internal/; \
    rm -rf /tmp/build/cld2
