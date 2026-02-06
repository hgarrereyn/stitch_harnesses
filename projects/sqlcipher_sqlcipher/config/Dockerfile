ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    libssl-dev ca-certificates pkg-config \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN ./configure \
    --prefix=/fuzz/install \
    --with-tempstore=yes \
    --disable-shared \
    --enable-static \
    CFLAGS="-DSQLITE_HAS_CODEC -DSQLITE_EXTRA_INIT=sqlcipher_extra_init -DSQLITE_EXTRA_SHUTDOWN=sqlcipher_extra_shutdown" \
    LDFLAGS="-lcrypto"

RUN make -j"$(nproc)" && make install
