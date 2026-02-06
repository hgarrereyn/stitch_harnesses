ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install the http_parser component as a static library
RUN set -eux; \
    apt-get update; \
    apt-get install -y --no-install-recommends ca-certificates make binutils; \
    rm -rf /var/lib/apt/lists/*; \
    mkdir -p /fuzz/install/include /fuzz/install/lib /work; \
    cd /work; \
    gf_libafl_cc -O2 -fPIC -I/fuzz/src/components/http_parser/include -c /fuzz/src/components/http_parser/src/http_parser.c -o http_parser.o; \
    ar rcs libhttp_parser.a http_parser.o; \
    install -m 0644 libhttp_parser.a /fuzz/install/lib/; \
    install -m 0644 /fuzz/src/components/http_parser/include/http_parser.h /fuzz/install/include/
