ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any required packages
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libabsl-dev \
 && rm -rf /var/lib/apt/lists/*

# Build a minimal static library from the project using the required compilers
# and install public headers. We avoid Bazel to ensure the required compiler
# wrappers are used and to keep dependencies minimal.
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p ${PREFIX}/include/grpc_transcoding ${PREFIX}/lib; \
    # Install all public headers
    cp -r /fuzz/src/src/include/grpc_transcoding/*.h ${PREFIX}/include/grpc_transcoding/; \
    # Build a small static library for http_template (header-only users can link against this)
    stitch_libafl_cxx -I/fuzz/src/src/include -O2 -fPIC -c /fuzz/src/src/http_template.cc -o /tmp/http_template.o; \
    ar rcs ${PREFIX}/lib/libgrpc_httpjson_http_template.a /tmp/http_template.o; \
    ranlib ${PREFIX}/lib/libgrpc_httpjson_http_template.a; \
    rm -f /tmp/http_template.o
