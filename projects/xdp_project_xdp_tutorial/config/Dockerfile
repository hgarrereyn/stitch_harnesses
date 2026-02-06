ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN dpkg --add-architecture i386 \
 && apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    git pkg-config clang-17 libelf-dev zlib1g-dev libc6-dev-i386 linux-libc-dev:i386 libpcap-dev libbpf-dev ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Ensure submodules are available (needed for libxdp source)
RUN if [ -f .gitmodules ]; then git submodule update --init --recursive; fi

# Use fuzzing compilers for userland, but clang-17 for BPF code
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx
ENV CLANG=clang-17
ENV ARCH_INCLUDES="-I/usr/include -I/usr/include/x86_64-linux-gnu -I/usr/include/i386-linux-gnu"

# Configure, build static libxdp only, and install to /fuzz/install
RUN cd lib/xdp-tools && ./configure
RUN make -C lib/xdp-tools BUILD_STATIC_ONLY=1 libxdp \
 && make -C lib/xdp-tools DESTDIR=/fuzz/install PREFIX= BUILD_STATIC_ONLY=1 libxdp_install
