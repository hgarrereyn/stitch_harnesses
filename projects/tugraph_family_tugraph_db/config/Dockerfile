ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      libboost-all-dev \
    && rm -rf /var/lib/apt/lists/*

# Install headers
RUN mkdir -p /fuzz/install/include && \
    mkdir -p /fuzz/install/lib && \
    cp -r /fuzz/src/include/* /fuzz/install/include/

# Build a tiny static library named liblgraph.a that implements minimal exception symbols
RUN cat > /tmp/min.cpp <<'EOF' && \
    stitch_libafl_cxx -c /tmp/min.cpp -I/fuzz/install/include -o /tmp/min.o && \
    echo "int tugraph_dummy(void){return 0;}" > /tmp/dummy.c && \
    stitch_libafl_cc -c /tmp/dummy.c -o /tmp/dummy.o && \
    ar rcs /fuzz/install/lib/liblgraph.a /tmp/min.o /tmp/dummy.o && \
    rm -f /tmp/min.cpp /tmp/min.o /tmp/dummy.c /tmp/dummy.o
#include "lgraph/lgraph_exceptions.h"
namespace lgraph_api {
const char* ErrorCodeToString(ErrorCode) { return "Error"; }
const char* ErrorCodeDesc(ErrorCode) { return "Error"; }
LgraphException::LgraphException(ErrorCode code)
    : code_(code) {
  msg_ = ""; what_ = "[Error]"; }
LgraphException::LgraphException(ErrorCode code, const std::string& msg)
    : code_(code), msg_(msg) {
  what_ = msg_; }
LgraphException::LgraphException(ErrorCode code, const char* msg)
    : code_(code), msg_(msg) {
  what_ = msg_; }
}
EOF
