ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library from rTorrent's utils/lockfile component to provide a linkable target.
# This avoids heavy external dependencies (libtorrent, ncurses, etc.) while still using rTorrent code.

RUN mkdir -p /fuzz/install/lib /fuzz/install/include/utils

# Copy and build the minimal component
# Generate an empty config.h expected by source files that include it.
RUN set -eux; \
    : "Create empty config.h to satisfy includes"; \
    echo "/* generated empty config for fuzzing build */" > /fuzz/src/config.h; \
    cd /fuzz/src/src/utils; \
    gf_libafl_cxx -I/fuzz/src -I/fuzz/src/src -c lockfile.cc -o /tmp/lockfile.o; \
    ar rcs /fuzz/install/lib/librtorrent_utils.a /tmp/lockfile.o; \
    cp /fuzz/src/src/utils/lockfile.h /fuzz/install/include/utils/lockfile.h

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
ENV PREFIX=/fuzz/install
