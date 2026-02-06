ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    pkg-config \
    binutils \
    libtermkey-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Build a static library directly from the amalgamated vis.c and install headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include /fuzz/install/share/vis \
 && stitch_libafl_cc -std=c99 -DNDEBUG -DVERSION=\"v0.0\" -DVIS_PATH=\"/fuzz/install/share/vis\" -DVIS_INTERNAL= -O2 -I. $(pkg-config --cflags termkey) -c vis.c -o vis.o \
 && ar rcs /fuzz/install/lib/libvis.a vis.o \
 && cp -t /fuzz/install/include \
    vis.h ui.h view.h text-regex.h array.h buffer.h text.h util.h \
    text-motions.h text-objects.h vis-core.h sam.h vis-subprocess.h map.h text-util.h \
 && printf '#include <termkey.h>\n#include "util.h"\n#include "vis.h"\n' > /fuzz/install/include/vis_public.h
