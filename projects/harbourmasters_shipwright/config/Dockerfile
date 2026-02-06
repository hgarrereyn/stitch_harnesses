ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal deps; project submodules are not vendored in this snapshot, so just stage headers for consumers
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

# Install headers as a stand-in SDK so fuzz harnesses can include them
RUN mkdir -p /fuzz/install/include && \
    if [ -d /fuzz/src/soh/include ]; then cp -r /fuzz/src/soh/include/* /fuzz/install/include/; fi && \
    true
