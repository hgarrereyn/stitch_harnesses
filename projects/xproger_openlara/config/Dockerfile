ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed to create a static archive
RUN apt-get update && apt-get install -y --no-install-recommends \
    binutils \
 && rm -rf /var/lib/apt/lists/*

# Install headers
RUN mkdir -p /fuzz/install/include/openlara && \
    cp -r /fuzz/src/src/* /fuzz/install/include/openlara/

# Build a tiny static library placeholder for linking
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN mkdir -p /fuzz/build /fuzz/install/lib && \
    echo "int openlara_dummy_symbol = 0;" > /fuzz/build/dummy.c && \
    ${CC} -c /fuzz/build/dummy.c -o /fuzz/build/dummy.o && \
    ar rcs /fuzz/install/lib/libopenlara.a /fuzz/build/dummy.o
