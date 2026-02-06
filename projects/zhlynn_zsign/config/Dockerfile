ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    libssl-dev \
    libminizip-dev \
    zlib1g-dev \
    make \
    && rm -rf /var/lib/apt/lists/*

# Build static library and install headers
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install
RUN set -eux; \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include; \
    cd /fuzz/src; \
    INCS="-I/fuzz/src/src -I/fuzz/src/src/common $(pkg-config --cflags openssl) $(pkg-config --cflags minizip)"; \
    SRCS=$(printf "%s\n" /fuzz/src/src/*.cpp /fuzz/src/src/common/*.cpp | grep -v "/zsign.cpp"); \
    OBJDIR=/tmp/objs; mkdir -p "$OBJDIR"; \
    for f in $SRCS; do \
      b=$(basename "$f" .cpp); \
      $CXX -O2 -fPIC $INCS -c "$f" -o "$OBJDIR/$b.o"; \
    done; \
    ar rcs ${PREFIX}/lib/libzsign.a $OBJDIR/*.o; \
    cp -a /fuzz/src/src/*.h ${PREFIX}/include/; \
    cp -a /fuzz/src/src/common/*.h ${PREFIX}/include/
