ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# RapidJSON is header-only: install headers into /fuzz/install
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

RUN mkdir -p /fuzz/install/include && \
    cp -r include/rapidjson /fuzz/install/include/
