ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools and fetch NGINX source to provide headers for building this module
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates wget xz-utils make perl \
    && rm -rf /var/lib/apt/lists/*

# Download and configure a minimal NGINX source tree (only to generate auto headers)
# We avoid optional deps (PCRE/zlib) so configure doesn't require them.
ENV NGINX_VERSION=1.25.5
RUN set -eux; \
    mkdir -p /tmp && cd /tmp; \
    wget -O nginx.tar.gz "http://nginx.org/download/nginx-${NGINX_VERSION}.tar.gz"; \
    tar -xzf nginx.tar.gz; \
    cd nginx-${NGINX_VERSION}; \
    ./configure \
      --without-http_rewrite_module \
      --without-http_gzip_module; \
    :

# Prepare install prefix
RUN mkdir -p /fuzz/install/lib /fuzz/install/include /fuzz/build

# Build a static library from the module sources using the fuzzing compilers
# and install headers and the archive. Also keep a copy of the nginx source
# tree (with generated headers) for consumers' include paths.
RUN set -eux; \
    cp -a /tmp/nginx-${NGINX_VERSION} /fuzz/install/nginx; \
    cd /fuzz/src/src; \
    INCS="-I/fuzz/install/nginx/src/core -I/fuzz/install/nginx/src/event -I/fuzz/install/nginx/src/http -I/fuzz/install/nginx/src/http/modules -I/fuzz/install/nginx/src/os/unix -I/fuzz/install/nginx/objs"; \
    for c in *.c; do \
      gf_libafl_cc -O2 -fPIC $INCS -c "$c" -o "/fuzz/build/${c%.c}.o"; \
    done; \
    ar rcs /fuzz/install/lib/libheaders_more.a /fuzz/build/*.o; \
    cp -a *.h /fuzz/install/include/
