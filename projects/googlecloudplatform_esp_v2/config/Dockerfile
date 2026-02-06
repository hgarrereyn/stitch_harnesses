ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    libabsl-dev \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

# Build a minimal static library for the path matcher component and install headers
RUN set -eux; \
    mkdir -p "$PREFIX/lib" "$PREFIX/include/src/api_proxy/path_matcher" /tmp/build; \
    cd /fuzz/src/src/api_proxy/path_matcher; \
    # Compile object files
    stitch_libafl_cxx -O2 -fPIC -I/fuzz/src -I/fuzz/src/src -c http_template.cc -o /tmp/build/http_template.o; \
    stitch_libafl_cxx -O2 -fPIC -I/fuzz/src -I/fuzz/src/src -c path_matcher_node.cc -o /tmp/build/path_matcher_node.o; \
    stitch_libafl_cxx -O2 -fPIC -I/fuzz/src -I/fuzz/src/src -c path_matcher.cc -o /tmp/build/path_matcher.o; \
    # Create static library
    ar rcs "$PREFIX/lib/libespv2_pathmatcher.a" /tmp/build/http_template.o /tmp/build/path_matcher_node.o /tmp/build/path_matcher.o; \
    # Install headers (avoid headers pulling in protobuf dependency)
    cp -a /fuzz/src/src/api_proxy/path_matcher/http_template.h "$PREFIX/include/src/api_proxy/path_matcher/"; \
    cp -a /fuzz/src/src/api_proxy/path_matcher/path_matcher_node.h "$PREFIX/include/src/api_proxy/path_matcher/"; \
    cp -a /fuzz/src/src/api_proxy/path_matcher/path_matcher.h "$PREFIX/include/src/api_proxy/path_matcher/"; \
    true
