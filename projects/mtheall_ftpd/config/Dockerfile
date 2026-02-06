ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal setup: we only install binutils to create a static archive.
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    binutils \
 && rm -rf /var/lib/apt/lists/*

# Install headers and create an empty static library placeholder for linking
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -r /fuzz/src/include/* /fuzz/install/include/ \
 && bash -lc 'ar rcs /fuzz/install/lib/libftpd.a'

