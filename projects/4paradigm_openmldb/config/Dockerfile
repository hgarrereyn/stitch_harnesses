ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    git \
    file \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Install public headers only (header-only UDF API)
RUN mkdir -p /fuzz/install/include/base /fuzz/install/include/udf \
 && cp -v /fuzz/src/include/base/*.h /fuzz/install/include/base/ \
 && cp -v /fuzz/src/include/udf/openmldb_udf.h /fuzz/install/include/udf/
