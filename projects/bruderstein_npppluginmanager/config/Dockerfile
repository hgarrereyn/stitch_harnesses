ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install

# Build static library: minizip unzip (portable parts only)
RUN set -eux; \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include; \
    cd /fuzz/src/unzip/src; \
    $CC -I/fuzz/src/unzip/include -fPIC -O2 -DTCHAR=char -c ioapi.c unzip.c; \
    ar rcs libunzip.a ioapi.o unzip.o; \
    cp libunzip.a ${PREFIX}/lib/; \
    cp /fuzz/src/unzip/include/*.h ${PREFIX}/include/; \
    echo 'Build and install complete.'
