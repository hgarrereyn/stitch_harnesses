ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for tmux
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake pkg-config bison \
    libevent-dev libncurses-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV INSTALL_PREFIX=/fuzz/install
ENV SRC=/fuzz/src

# Build tmux (executable) using fuzzing compilers
WORKDIR ${SRC}
RUN sh autogen.sh
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx
RUN ./configure --prefix=${INSTALL_PREFIX}
RUN make -j"$(nproc)"

# Create a tiny shim static library and header to allow linking tests
RUN mkdir -p ${INSTALL_PREFIX}/lib ${INSTALL_PREFIX}/include \
 && printf "#include <stdint.h>\nint tmux_public_sum(int a, int b) { return a + b; }\n" > /tmp/tmux_shim.c \
 && gf_libafl_cc -c -O2 -fPIC /tmp/tmux_shim.c -o /tmp/tmux_shim.o \
 && ar rcs ${INSTALL_PREFIX}/lib/libtmux.a /tmp/tmux_shim.o \
 && printf "#ifndef TMUX_PUBLIC_H\n#define TMUX_PUBLIC_H\n#ifdef __cplusplus\nextern \"C\" {\n#endif\nint tmux_public_sum(int a, int b);\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > ${INSTALL_PREFIX}/include/tmux_public.h
