ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra runtime deps required. Provide basic tools for possible downstream builds.
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends ca-certificates && \
    rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Install headers (header-only library) to /fuzz/install
RUN mkdir -p /fuzz/install/include && \
    cp -r include/* /fuzz/install/include/
