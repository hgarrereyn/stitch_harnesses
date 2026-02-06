ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static lib from the SDK: snappy (subset of tier1)
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
ENV PREFIX=/fuzz/install

WORKDIR /fuzz/src
RUN set -eux; \
    mkdir -p /tmp/build_snappy "$PREFIX"/lib "$PREFIX"/include; \
    incroot=/fuzz/src/src/public; \
    # Build snappy subset
    for f in src/tier1/snappy.cpp src/tier1/snappy-stubs-internal.cpp src/tier1/snappy-sinksource.cpp; do \
      "$CXX" -O2 -fPIC -DPOSIX -DLINUX -D_LINUX -DGNUC -I"$incroot" -I"$incroot"/tier0 -I"$incroot"/tier1 -c "$f" -o /tmp/build_snappy/$(basename "$f" .cpp).o; \
    done; \
    ar rcs "$PREFIX"/lib/libtier1_snappy.a /tmp/build_snappy/*.o; \
    # Install public headers for snappy API and needed tier0 headers
    mkdir -p "$PREFIX"/include/tier1 "$PREFIX"/include/tier0; \
    cp -r "$incroot"/tier1/snappy*.h "$PREFIX"/include/tier1/; \
    cp -r "$incroot"/tier0/*.h "$PREFIX"/include/tier0/; \
    # Also expose a couple of commonly used headers at root level (optional)
    cp -r "$incroot"/*.h "$PREFIX"/include/ || true
