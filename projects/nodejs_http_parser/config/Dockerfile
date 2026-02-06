ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build http-parser as a static library and install headers
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Build only the static library (libhttp_parser.a) using the required compiler
RUN make clean || true \
 && make CC=gf_libafl_cc AR=ar package \
 && install -d /fuzz/install/include /fuzz/install/lib \
 && install -m644 http_parser.h /fuzz/install/include/ \
 && install -m644 libhttp_parser.a /fuzz/install/lib/
