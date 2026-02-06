ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal install: we only need binutils for `ar` to create a static archive.
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    binutils \
 && rm -rf /var/lib/apt/lists/*

# Create install prefix
ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/lib ${PREFIX}/include

# "Build" and install: copy public headers and create an empty static libpag.a
WORKDIR /fuzz/src
RUN cp -r include/pag ${PREFIX}/include/
# Create an empty static library to satisfy the linker when no symbols are referenced.
RUN bash -lc "test -f ${PREFIX}/lib/libpag.a || (mkdir -p /tmp/empty && cd /tmp/empty && echo | ar rcs ${PREFIX}/lib/libpag.a)"

# Ensure compilers are set (even though we don't compile the library here)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
