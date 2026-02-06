ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Header-only project: install headers to /fuzz/install/include
RUN set -eux; \
    mkdir -p /fuzz/install/include; \
    cd /fuzz/src; \
    cp -r include/rest_rpc /fuzz/install/include/; \
    # Provide third-party headers expected by includes like <asio.hpp> and <ylt/...>
    cp -r thirdparty/asio/asio.hpp /fuzz/install/include/ || true; \
    cp -r thirdparty/asio/asio /fuzz/install/include/ || true; \
    cp -r thirdparty/ylt /fuzz/install/include/ || true

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Nothing to build (header-only).