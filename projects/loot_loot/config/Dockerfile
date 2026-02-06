ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Prepare install prefix
RUN mkdir -p /fuzz/install/include/loot_loot /fuzz/install/lib

# Install a subset of self-contained headers from the source tree
RUN install -m 0644 -D /fuzz/src/src/gui/state/game/game_id.h /fuzz/install/include/loot_loot/game_id.h \
 && install -m 0644 -D /fuzz/src/src/gui/state/game/load_order_backup.h /fuzz/install/include/loot_loot/load_order_backup.h

# Build a tiny empty static library so linking succeeds
RUN echo "int __loot_loot_dummy = 0;" > /tmp/empty.c \
    && gf_libafl_cc -c /tmp/empty.c -o /tmp/empty.o \
    && ar rcs /fuzz/install/lib/libloot_loot.a /tmp/empty.o \
    && rm -f /tmp/empty.c /tmp/empty.o
