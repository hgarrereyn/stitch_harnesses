ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install clib and also produce a static library of common APIs
RUN apt-get update && apt-get install -y --no-install-recommends \
    libcurl4-openssl-dev curl ca-certificates binutils \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Build the project binaries (ensures deps are built too)
ENV CC=gf_libafl_cc
RUN make -j"$(nproc)"

# Install the binaries
RUN make install PREFIX=/fuzz/install

# Create and install a static library for the common clib APIs and install headers and vendored includes
RUN set -eux; \
    mkdir -p /fuzz/install/lib /fuzz/install/include/clib; \
    CF="$(curl-config --cflags) -std=c99 -Ideps -Wall -Wno-unused-function -U__STRICT_ANSI__"; \
    for f in src/common/*.c; do \
      gf_libafl_cc $CF -c "$f" -o "$(basename "$f" .c).o"; \
    done; \
    find deps -name '*.o' > /tmp/dep_objs; \
    ar rcs /fuzz/install/lib/libclib.a *.o $(cat /tmp/dep_objs); \
    cp -t /fuzz/install/include/clib src/common/*.h src/version.h; \
    # Install vendored headers under include so includes like "list/list.h" resolve
    mkdir -p /fuzz/install/include; \
    find deps -type d -maxdepth 1 -mindepth 1 -exec bash -c 'd="$1"; [ -n "$(ls "$d"/*.h 2>/dev/null)" ] && cp -r "$d" /fuzz/install/include/' _ {} \; 
