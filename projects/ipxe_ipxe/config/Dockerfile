ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install binutils for static archive tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends binutils ca-certificates && rm -rf /var/lib/apt/lists/*

# Build a minimal static library from iPXE sources and install headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    printf "#ifndef IPXE_SHIM\n#define IPXE_SHIM\n#define FILE_LICENCE(x)\n#define DBG(...) do{}while(0)\n#endif\n" > /tmp/ipxe_shim.h && \
    mkdir -p /tmp/ipxe_root && \
    cp -r /fuzz/src/src/include/ipxe /tmp/ipxe_root/ && \
    cd /fuzz/src/src && \
    gf_libafl_cc -I/tmp/ipxe_root -include /tmp/ipxe_shim.h -c core/base64.c -o /tmp/base64.o && \
    ar rcs /fuzz/install/lib/libipxe.a /tmp/base64.o && \
    cp -r /tmp/ipxe_root/ipxe /fuzz/install/include/
