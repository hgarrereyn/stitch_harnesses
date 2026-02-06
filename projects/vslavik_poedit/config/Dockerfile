ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install headers for dependencies needed to compile Poedit headers we use
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libwxgtk3.0-gtk3-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Create install prefix and install selected public headers
ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib && \
    cp /fuzz/src/src/static_ids.h ${PREFIX}/include/

# Build a tiny static library stub to satisfy linking
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN echo "void __poedit_stub(){}" > /tmp/stub.c && \
    ${CC} -c /tmp/stub.c -o /tmp/stub.o && \
    ar rcs ${PREFIX}/lib/libpoeditstub.a /tmp/stub.o && \
    rm -f /tmp/stub.c /tmp/stub.o
