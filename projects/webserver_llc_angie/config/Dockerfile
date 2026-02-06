ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    perl \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure Angie with minimal features and our compilers
ENV CC=gf_libafl_cc
RUN ./configure \
    --prefix=/fuzz/install \
    --with-cc=gf_libafl_cc \
    --with-cc-opt="$CFLAGS" \
    --with-ld-opt="$LDFLAGS" \
    --without-pcre \
    --without-pcre2 \
    --without-http_rewrite_module \
    --without-http_gzip_module

# Build
RUN make -j"$(nproc)"

# Install headers and create static libraries
RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib; \
    # Copy all headers flat into include dir
    find src -type f -name '*.h' -exec cp -v {} /fuzz/install/include/ \; ; \
    # Copy generated configuration headers
    cp -v objs/ngx_auto_config.h objs/ngx_auto_headers.h /fuzz/install/include/; \
    # Full archive (may contain many objects)
    ar rcs /fuzz/install/lib/libangie.a $(find objs -type f -name '*.o'); \
    # Minimal archive with only a couple of safe objects
    ar rcs /fuzz/install/lib/libangie_min.a \
        objs/src/core/ngx_crc32.o \
        objs/src/core/ngx_string.o
