ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    pkg-config \
    libssl-dev \
 && rm -rf /var/lib/apt/lists/*

# Build a small static library from non-Qt core sources (web client utilities)
ENV PREFIX=/fuzz/install
RUN mkdir -p /fuzz/build "$PREFIX"/lib "$PREFIX"/include/soramimi_guitar
WORKDIR /fuzz/build

# Compile objects with the provided clang wrappers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN SRCDIR=/fuzz/src/src && \
    $CXX -O2 -fPIC -I"$SRCDIR" -I"$SRCDIR/common" -c "$SRCDIR/webclient.cpp" -o webclient.o && \
    $CXX -O2 -fPIC -I"$SRCDIR" -I"$SRCDIR/common" -c "$SRCDIR/inetresolver.cpp" -o inetresolver.o && \
    $CXX -O2 -fPIC -I"$SRCDIR" -I"$SRCDIR/common" -c "$SRCDIR/urlencode.cpp" -o urlencode.o && \
    $CXX -O2 -fPIC -I"$SRCDIR" -I"$SRCDIR/common" -c "$SRCDIR/common/base64.cpp" -o base64.o && \
    $CXX -O2 -fPIC -I"$SRCDIR" -I"$SRCDIR/common" -c "$SRCDIR/common/charvec.cpp" -o charvec.o && \
    ar rcs libguitarwc.a webclient.o inetresolver.o urlencode.o base64.o charvec.o && \
    cp libguitarwc.a "$PREFIX"/lib/

# Install public headers
RUN SRCDIR=/fuzz/src/src && \
    cp "$SRCDIR/webclient.h" "$PREFIX"/include/soramimi_guitar/ && \
    cp "$SRCDIR/inetresolver.h" "$PREFIX"/include/soramimi_guitar/ && \
    cp "$SRCDIR/urlencode.h" "$PREFIX"/include/soramimi_guitar/
