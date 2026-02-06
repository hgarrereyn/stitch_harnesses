ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra heavy deps needed for the portable subset
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build a tiny static library from the portable Catime modules
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz

# Compile selected portable source(s) into a static library
RUN mkdir -p build && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cd build && \
    ${CC} -c -O2 -I/fuzz/src/include /fuzz/src/src/utils/string_safe.c && \
    ar rcs libcatime.a *.o && \
    cp libcatime.a /fuzz/install/lib/

# Install headers (we will primarily use portable ones)
RUN mkdir -p /fuzz/install/include/utils && \
    cp /fuzz/src/include/utils/string_safe.h /fuzz/install/include/utils/ && \
    cp /fuzz/src/include/utils/natural_sort.h /fuzz/install/include/utils/

ENV CPATH=/fuzz/install/include:${CPATH}
ENV LIBRARY_PATH=/fuzz/install/lib:${LIBRARY_PATH}
