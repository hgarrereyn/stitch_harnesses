ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Minimal tools
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates make && rm -rf /var/lib/apt/lists/*

# Install a minimal SDK layout for kioarchive6 to allow building against headers
RUN mkdir -p /fuzz/install/include/KioArchive6 /fuzz/install/lib && \
    printf "#pragma once\n#define LIBKIOARCHIVE_EXPORT\n" > /fuzz/install/include/KioArchive6/libkioarchive_export.h && \
    printf "#pragma once\n#define KIOARCHIVE_VERSION_STR \"6.0.0\"\n" > /fuzz/install/include/KioArchive6/kioarchive_version.h && \
    cp /fuzz/src/archive/kio_archivebase.h /fuzz/install/include/KioArchive6/ && \
    echo "int __kioarchive6_placeholder() { return 0; }" > /tmp/placeholder.c && \
    stitch_libafl_cc -c /tmp/placeholder.c -o /tmp/placeholder.o && \
    ar rcs /fuzz/install/lib/libkioarchive6.a /tmp/placeholder.o && \
    rm -f /tmp/placeholder.c /tmp/placeholder.o
