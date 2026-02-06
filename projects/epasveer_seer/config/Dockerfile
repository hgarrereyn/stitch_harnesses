ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal Qt6 development package for core utilities
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      qt6-base-dev \
    && rm -rf /var/lib/apt/lists/*

# Prepare install directories and install headers from mounted source tree
RUN mkdir -p /fuzz/install/include/seer /fuzz/install/lib && \
    cp -a /fuzz/src/src/SeerUtl.h /fuzz/src/src/QStringPair.h /fuzz/install/include/seer/

# Build a small static library for Seer utilities to link against
RUN stitch_libafl_cxx -fPIC -I/usr/include/x86_64-linux-gnu/qt6 -c /fuzz/src/src/SeerUtl.cpp -o /tmp/SeerUtl.o && \
    ar rcs /fuzz/install/lib/libseerutl.a /tmp/SeerUtl.o && \
    rm -f /tmp/SeerUtl.o
