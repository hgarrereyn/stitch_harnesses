ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies (Boost headers)
RUN apt-get update && apt-get install -y --no-install-recommends \
    libboost-dev \
 && rm -rf /var/lib/apt/lists/*

# Prepare install prefix
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install SRC=/fuzz/src
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib

# Install public headers (only portable, header-only parts)
RUN mkdir -p ${PREFIX}/include/Explorer++ \
 && cp ${SRC}/Explorer++/Explorer++/ValueWrapper.h ${PREFIX}/include/Explorer++/ValueWrapper.h

# Build a tiny static library to link against
RUN bash -lc 'echo "void explorerpp_stub(){}" > /tmp/stub.c && \
    ${CC} -c -o /tmp/stub.o /tmp/stub.c && \
    ar rcs ${PREFIX}/lib/libexplorerpp.a /tmp/stub.o && \
    rm -f /tmp/stub.c /tmp/stub.o'
