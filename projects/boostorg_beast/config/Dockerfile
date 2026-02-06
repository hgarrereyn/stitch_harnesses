ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libboost-all-dev \
    && rm -rf /var/lib/apt/lists/*

ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN cp -r /usr/include/boost ${PREFIX}/include/ && \
    cp -r /fuzz/src/include/boost/* ${PREFIX}/include/boost/

# Patch for compatibility with older Boost in Ubuntu 22.04
RUN sed -i 's#<boost/core/detail/static_assert.hpp>#<boost/static_assert.hpp>#' \
    ${PREFIX}/include/boost/beast/core/detail/config.hpp || true
