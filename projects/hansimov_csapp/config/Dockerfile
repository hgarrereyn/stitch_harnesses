ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any extra dependencies needed to build the project
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates git make sed && rm -rf /var/lib/apt/lists/*

# Build the static library using the provided wrappers
# - Patch the Makefile to use gf_libafl_cc instead of gcc for all objects
# - Build 64-bit static library
RUN set -eux; \
    cd /fuzz/src/_codes/code/src; \
    sed -i 's/^CC = .*/CC = gf_libafl_cc/' Makefile; \
    sed -i 's/\tgcc \$(CFLAGS)/\t$(CC) $(CFLAGS)/g' Makefile; \
    make -j$(nproc) all; \
    mkdir -p /fuzz/install/lib /fuzz/install/include; \
    cp -v ../lib/libcsapp64.a /fuzz/install/lib/; \
    cp -v ../include/*.h /fuzz/install/include/

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig
